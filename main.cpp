#include "biblioteca/string.hpp"
#include "biblioteca/tokens.hpp"
#include "biblioteca/coll.hpp"
#include "biblioteca/array.hpp"
#include "biblioteca/arrays.hpp"
#include "biblioteca/string.hpp"
#include "biblioteca/BitWriter.hpp"
#include "bitReader.hpp"
#include "bitWriter.hpp"
#include "huffmanSetup.hpp"
#include "progress.hpp"
#include <iostream>
using namespace std;

// Algoritmo huffman, ejercicio integrador
// 1. Contar frecuencias de cada caracter
Array<int> countFrecuency(string fileName){
    Array<int> frecuency(256);
    for (int i = 0; i < frecuency.length(); i++)
    {
        frecuency[i] = 0;
    }
    BitReader br(fileName);
    while (br.hasNext())
    {
        frecuency[br.next()]++;
    }
    return frecuency;
}

// 2 Crear lista enlazada de nodos que ordena ascendentemente por frecuencia, el nodo con menor frecuencia es el primero

struct Node{
    int frecuency;
    int byte;
    Node* left;
    Node* right;
};

Coll<Node> createList(Array<int> frecuency){
    Coll<Node> list;
    for (int i = 0; i < frecuency.size(); i++){
        if (frecuency[i] > 0){
            Node* node = new Node;
            node->frecuency = frecuency[i];
            node->byte = i;
            node->left = NULL;
            node->right = NULL;
            list.add(node);
        }
    }
    return list;
}

// 3. Crear arbol de huffman
Node* createHuffmanTree(Coll<Node> list){
    while (list.size() > 1){
        Node* node = new Node;
        node->frecuency = list[0]->frecuency + list[1]->frecuency;
        node->byte = -1;
        node->left = list[0];
        node->right = list[1];
        list.remove(0);
        list.remove(0);
        int i = 0;
        while (i < list.size() && list[i]->frecuency < node->frecuency){
            i++;
        }
        list.add(i,node);
    }
    return list[0];
}

// 4. Crear tabla de codigos
Array<string> createTable(Node* root){
    Array<string> table(256);
    for (int i = 0; i < table.length(); i++){
        table[i] = "";
    }
    Coll<Node*> list;
    list.add(root);
    while (list.size() > 0){
        Node* node = list[0];
        list.remove(0);
        if (node->byte != -1){
            table[node->byte] = node->code;
        }else{
            node->left->code = node->code + "0";
            node->right->code = node->code + "1";
            list.add(node->left);
            list.add(node->right);
        }
    }
    return table;
}

// 5. Codificar
void encode(string fileName, Array<string> table){
    BitWriter bw(fileName + ".huff");
    BitReader br(fileName);
    while (br.hasNext()){
        string code = table[br.next()];
        for (int i = 0; i < code.length(); i++){
            bw.write(code[i] == '1');
        }
    }
    bw.close();
}

// 6. Decodificar
void decode(string fileName, Node* root){
    BitReader br(fileName);
    BitWriter bw(fileName + ".dec");
    Node* node = root;
    while (br.hasNext()){
        if (node->byte != -1){
            bw.write(node->byte);
            node = root;
        }
        if (br.next()){
            node = node->right;
        }else{
            node = node->left;
        }
    }
    bw.close();
}

// 7. Liberar memoria
void freeMemory(Node* root){
    if (root->byte == -1){
        freeMemory(root->left);
        freeMemory(root->right);
    }
    delete root;
}

int main(int argc, char const *argv[])
{
    string fileName = "test.txt";
    Array<int> frecuency = countFrecuency(fileName);
    Coll<Node> list = createList(frecuency);
    Node* root = createHuffmanTree(list);
    Array<string> table = createTable(root);
    encode(fileName, table);
    decode(fileName + ".huff", root);
    freeMemory(root);
    return 0;
}

