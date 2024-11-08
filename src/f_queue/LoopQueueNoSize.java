package src.f_queue;

public class LoopQueueNoSize<E> implements Queue<E> {

  private E[] data;
  private int front, tail;

  public LoopQueueNoSize(int capacity) {
    // 主动浪费一个空间，用来区分空队列和满队列
    data = (E[]) new Object[capacity];
    front = tail = 0;
  }

  public LoopQueueNoSize() {
    this(10);
  }

  @Override
  public boolean isEmpty() {
    return front == tail && data.length == 0;
  }

  public boolean isFull() {
    if (tail > front) {
      return (tail - front == data.length);
    }
    return tail > 0 && tail == front;
  }

  /**
   * 动态计算当前队列的容量
   * 
   * 1. 如果 tail > front，说明 tail 还没有走到超出数组容量，直接相减即可；
   * 2. 否则，从 front 开始数到数组结尾（data.length - front），然后把循环回去的 tail 加上即可
   * tail 指向最后一个元素的下一个元素，所以 tail 的值实际上就是循环回去插入的数量
   */
  @Override
  public int getSize() {
    if (isEmpty()) return 0;
    if (front < tail) {
      return tail - front;
    } else {
      return data.length - front + tail;
    }
  }

  @Override
  public void enqueue(E e) {
    if (getSize() == data.length) {
      resize(data.length * 2);
    }    
    data[tail] = e;
    tail = (tail + 1) % data.length;
  }

  @Override
  public E dequeue() {
    if (isEmpty()) {
      throw new RuntimeException("Queue is empty.");
    }
    E ret = data[front];
    data[front] = null;
    front = (front + 1) % data.length;

    if (getSize() == data.length / 4 && data.length / 2 != 0) {
      resize(data.length / 2);
    }
    return ret;
  }

  private void resize(int newCapacity) {
    E[] newData = (E[])new Object[newCapacity];
    int size = getSize();
    for (int i = 0; i < size; i++) {
      newData[i] = data[(i + front) % data.length];
    }
    data = newData;
    front = 0;
    tail = size;
  }

  @Override
  public String toString() {
    StringBuilder builder = new StringBuilder();
    builder.append("LoopingQueue: front [");
    // for (int i = front; i != tail; i = (i + 1) % data.length) {
    //   builder.append(data[i]);
    //   if ((i + 1) % data.length != tail) {
    //     builder.append(", ");
    //   }
    // }
    int size = getSize();
    for (int i = 0; i < size; i++) {
      builder.append(data[(i + front) % data.length]);
      builder.append(", ");
    }
    builder.append("] tail");
    return builder.toString();
  }

}
