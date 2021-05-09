#ifndef REALTIME_FIR
#   define REALTIME_FIR

typedef unsigned int uint32;

template<typename T>
class RT_FIR {
    private:
        typedef struct node {
            T value;
            T weight;
            struct node *next;
        } node;
        node *head;
        T last_output;
    public:
        RT_FIR (uint32 n_value, T *weight, T init_value = 0);
        T add (T value);
        T output( );
};

template <typename T>
RT_FIR<T>::RT_FIR (uint32 n_value, T *weight, T init_value) {
    node *current;
    last_output = 0;
    if (n_value == 0)
        return;

    current = (node*) malloc(sizeof(node));
    this->head = current;
    current->value = init_value;
    current->weight = weight[0];
    for (uint32 i = 1; i < n_value; i++)
    {
        current->next = (node*) malloc(sizeof(node));
        current = current->next;
        current->value = init_value;
        current->weight = weight[i];
    }
    current->next = this->head;
}

template <typename T>
T RT_FIR<T>::add (T value) {
    this->head->value = value;
    this->head = this->head->next;
    this->last_output = output();
    return this->last_output;
}

template <typename T>
T RT_FIR<T>::output( ) {
    T filtered = 0;
    void *_ = this->head;
    do {
        filtered += this->head->weight * this->head->value;
        this->head = this->head->next;
    } while ((node*) _ != this->head);
    return filtered;
}

#endif // REALTIME_FIR
