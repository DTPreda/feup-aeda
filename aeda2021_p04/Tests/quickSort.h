#include <vector>

template <class T>
void swap(const T &first, const T &second){
    T temp;
    temp = second;
    second = first;
    first = temp;
}

template <class T>
int median3(std::vector<T> &v, int left, int right){
    int middle = (left + right) /2;
    if(v[middle] < v[left]){
        swap(v[middle], v[left]);
    }
    if(v[right] < v[left]){
        swap(v[right], v[left]);
    }
    if (v[right] < v[middle]){
        swap(v[right], v[middle]);
    }
    return middle;
}

template <class T>
int median3(std::vector<T> &v, int left, int right, bool comparator(T& first, T& second)){
    int middle = (left + right) /2;
    if(comparator(v[middle], v[left])){
        swap(v[middle], v[left]);
    }
    if(comparator(v[right], v[left])){
        swap(v[right], v[left]);
    }
    if (comparator(v[right], v[middle])){
        swap(v[right], v[middle]);
    }
    return middle;
}

template <class T>
void quickSort(std::vector<T> &v, int left, int right){
    if(left < right){
        int middle = median3(v, left, right);
        int separation = left;
        swap(v[middle], v[right]);
        for(int i = left; i < right; i++){
            if(v[i] < v[right]){
                swap(v[i], v[separation]);
                separation++;
            }
        }
        swap(v[right], v[separation]);
        quickSort(v, left, separation);
        quickSort(v, separation + 1, right);
    }
}

template <class T>
void quickSort(std::vector<T> &v, int left, int right, bool comparator(T& first, T& second)){
    if(left < right){
        int middle = median3(v, left, right, comparator);
        int separation = left;
        swap(v[middle], v[right]);
        for(int i = left; i < right; i++){
            if(comparator(v[i], v[right])){
                swap(v[i], v[separation]);
                separation++;
            }
        }
        swap(v[right], v[separation]);
        quickSort(v, left, separation, comparator);
        quickSort(v, separation + 1, right, comparator);
    }
}

template <class T>
void quickSort(std::vector<T> &v){
    quickSort(v, 0, v.size() - 1);
}

template <class T>
void quickSort(std::vector<T> &v, bool comparator(T& first, T& second)){
    quickSort(v, 0, v.size() - 1, comparator);
}