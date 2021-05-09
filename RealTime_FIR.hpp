#ifndef REALTIME_FIR
#   define REALTIME_FIR
typedef unsigned int uint32;

template<typename T>
class RT_FIR {
    private:
        typedef struct node {
            T value;
            struct node *next;
        } node;
        node *in;
        uint32 b;
        T *weight;
        T last_output;
    public:
        RT_FIR (uint32 n_value, T *weight, T init_value = 0);
        T add (T value);
        T compute( );
        T getLastOutput( );
};

template <typename T>
RT_FIR<T>::RT_FIR (uint32 n_value, T *weight, T init_value) {
    node *current_input;
    last_output = 0;
    this->b = n_value;

    this->weight = (T*) malloc(sizeof(T) * n_value);
    memcpy(this->weight, weight, sizeof(T) * n_value);
    // init circular list
    current_input = (node*) malloc(sizeof(node));
    this->in = current_input;
    current_input->value = init_value;
    for (uint32 i = 1; i < n_value; i++) {
        current_input->next = (node*) malloc(sizeof(node));
        current_input = current_input->next;
        current_input->value = init_value;
    }
    current_input->next = this->in;
}

template <typename T>
T RT_FIR<T>::add (T value) {
    // append last input vale and circle
    this->in->value = value;
    this->in = this->in->next;
    // compute filtering and return the filtered value
    this->last_output = compute();
    return this->last_output;
}

template <typename T>
T RT_FIR<T>::compute( ) {
    T filtered = 0;
    uint32 w_index, counter = 0;
    void *_ = this->in;
    do {
        w_index = this->b - counter - 1;
        filtered += this->in->value * this->weight[w_index];
        this->in = this->in->next;
        counter ++;
    } while ((node*) _ != this->in);
    return filtered;
}

template <typename T>
T RT_FIR<T>::getLastOutput( ) {
    return this->last_output;
}
#endif // REALTIME_FIR
