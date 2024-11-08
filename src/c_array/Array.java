package src.c_array;

public class Array<E> {

    private E[] data;
    private int currentSize;

    public Array(int capacity) {
        data = (E[])(new Object[capacity]);
        currentSize = 0;
    }

    public Array() {
        this(10);
    }

    public int getSize() {
        return currentSize;
    }

    /**
     * There is difference between the length of the internal array and the `size` property.
     * - `the length of the internal array` is the maximum count that this structure can hold
     * - `size` property is the actual amount of this structure
     */
    public int getCapacity() {  
        return data.length;
    }

    public boolean isEmpty() {
        return currentSize == 0;
    }

    public E get(int index) {
        if (index < 0 || index >= currentSize) {
            throw new IllegalArgumentException("Invalid index: 0 <= index < currentSize");
        }
        return data[index];
    }

    public E getFirst() {
        return get(0);
    }

    public E getLast() {
        return get(currentSize - 1);
    }

    public void set(int index, E e) {
        if (index < 0 || index >= currentSize) {
            throw new IllegalArgumentException("Invalid index: 0 <= index < currentSize");
        }
        data[index] = e;
    }

    public void addFirst(E e) {
        add(0, e);
    }

    public void addLast(E e) {
        add(currentSize, e);
    }

    public void add(int index, E e) {
        // if the target index is lesser than 0, then it's an invalid index;
        // if the target index is greater than current size, then it's targeting an alone element, this is achieable 
        // as long as the target index is lesser than the capacity, but it will cause a lot troubles when the elements are not be adjacent to each other
        // so we're limit the index to be as: 0 <= index <= currentSize, to make all the element are stored compactly
        if (index < 0 || index > currentSize) {
            throw new IllegalArgumentException("Add failed, index should be greater that zero and less than.");
        }

        // If current size is equals to the capacity of the internal array
        // then there is no more room for another element, so we're quiting from here.
        // We'll try to resize the array if there is no enough room for another new element
        if (currentSize == data.length) {
            resize(data.length * 2);
        }

        // Insert the target element into the array
        // make room for the target element by shifting all the elements after target index by 1 position
        // 0 1 2 3 4 5 6 7 8 9
        // a b c d e f g ? ? ? 
        // a b x c d e f g ? ?
        // Start from the last element, and end at the target index,
        // because that's the target place, we need to make sure that position is empty
        for (int i = currentSize - 1; i >= index; i--) {
            // move the element one by one unitl there is an empty space at the target index
            data[i + 1] = data[i];
        }
        // place the target element at the target index
        data[index] = e;

        // Don't forget to add current size after inserting the new element
        currentSize ++;
    }

    public boolean contains(E e) {
        for (int i = 0; i < currentSize; i++) {
            if (data[i].equals(e)) {
                return true;
            }
        }
        return false;
    }

    public int find(E e) {
        for (int i = 0; i < currentSize; i++) {
            if (data[i].equals(e)) {
                return i;
            }
        }
        return -1;
    }


    public E remove(int index) {
        if (index < 0 || index >= currentSize) {
            throw new IllegalArgumentException("invalid index!");
        }

        E ret = data[index];
        // 0 1 2 3 4 5 6 7 8 9
        // a b c d e ? ? ? ? ?
        // a x c d e ? ? ? ? ?
        // a c d e ? ? ? ? ? ?
        // just shift all the elements on the right of the index to erase the target one
        // Actually, we don't need to care about the value of the original index of `currentSize`
        // Cause user will never access that value, it's not valid
        // !!! Bad
        // for (int i = index; i < currentSize; i++) {
        //     data[i] = data[i + 1];
        // }
        for (int i = index + 1; i < currentSize; i++) {
            data[i - 1] = data[i];
        }
        currentSize--;

        if (currentSize <= data.length / 2 && data.length / 2 != 0) {
            resize(data.length / 2);
        }
        
        return ret;
    }

    public E removeFirst() {
        return remove(0);
    }

    public E removeLast() {
        return remove(currentSize - 1);
    }

    public int removeElement(E e) {
        int index = find(e);
        if (index != -1) {
            remove(index);
        }
        return index;
    }

    @Override
    public String toString() {
        StringBuilder res = new StringBuilder();
        res.append(String.format("Array: currentSize = %d, capacity = %d\n", currentSize, data.length));
        res.append("[");
        for (int i = 0; i < currentSize; i++) {
            res.append(data[i]);
            if (i != currentSize - 1) {
                res.append(", ");
            }
        }
        res.append("]");
        return res.toString();
    }

    private void resize(int newSize) {
       E[] newArr = (E[])(new Object[newSize]);
       for (int i = 0; i <= currentSize - 1; i++) {
            newArr[i] = data[i];
       }
       data = newArr;
    }
    
}
