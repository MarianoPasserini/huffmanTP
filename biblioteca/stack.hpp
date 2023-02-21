template<typename T>
struct Stack
{
// implementacion a cargo del estudiante
};

// Prototipo: Stack<T> stack();
// Descripción: Crea una pila vacía.
// Retorna: Stack<T> – Una pila vacía, lista para usar.

template<typename T>
Stack<T> stack();

// Prototipo: T* stackPush(Stack<T>& st,T e);
// Descripción: Apila el elemento e.
// Parámetros:
// • Stack<T>& st - Pila.
// • T e – Elemento que se apilará.
// Retorna: T* – Dirección de memoria del elemento que se apiló.

template<typename T>
T* stackPush(Stack<T>& st,T e){
    T* aux = new T;
    *aux = e;
    st.push(aux);
    return aux;
}

// Prototipo: T stackPop(Stack<T>& st);
// Descripción: Desapila un elemento.
// Parámetro: Stack<T>& st - Pila.
// Retorna: T – Elemento que se desapiló.

template<typename T>
T stackPop(Stack<T>& st){
    T aux = *st.top();
    st.pop();
    return aux;
}

// Prototipo: bool stackIsEmpty(Stack<T>& st);
// Descripción: Indica si la pila está vacía.
// Parámetro: Stack<T>& st - Pila.
// Retorna: bool – true si la pila está vacía, false en caso contrario.

template<typename T>
bool stackIsEmpty(Stack<T>& st){
    return st.empty();
}

//Prototipo: int stackSize(Stack<T> st);
//Descripción: Devuelve la cantidad de elementos en la pila.
//Parámetro: Stack<T> st - Pila.

template<typename T>
int stackSize(Stack<T> st){
    return st.size();
}