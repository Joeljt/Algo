package others.Java.src.f_queue;

import others.Java.src.c_array.Array;

public class LoopQueue<E> implements Queue<E> {

  private E[] data;
  private int front, tail;
  private int size;

  public LoopQueue(int capacity) {
    data = (E[])new Object[capacity + 1];
    front = 0;
    tail = 0;
    size = 0;
  }

  public LoopQueue() {
    this(10);
  }

  public int getCapacity() {
    return data.length - 1;
  }

  @Override
  public boolean isEmpty() {
    return front == tail;
  }

  @Override
  public int getSize() {
    return size;
  }

  @Override
  public E getFront() {
    if (isEmpty()) {
      throw new RuntimeException("Queue is empty.");
    }
    return data[front];
  }

  @Override
  public void enqueue(E e) {
    // 检查队列是否已经满了，如果满了就要触发扩容
    if ((tail + 1) % data.length == front) {
      resize(getCapacity() * 2);
    }
    // 正常向数组尾部添加元素即可，
    data[tail] = e;
    // 维护 tail 的值，正常只需要 tail++ 即可，但是循环队列需要确保不越界
    tail = (tail + 1) % data.length;
    // 维护一下 size 字段，记录当前队列的元素数量
    size ++;
  }

  @Override
  public E dequeue() {
    if (isEmpty()) {
      throw new RuntimeException("Queue is empty.");
    }

    E ret = data[front];

    // 队首元素出队以后，需要维护 front 的值，向前进一位
    // 无论是入队还是出队，对应的角标 front 或者 tail 都是向前一步
    // 入队：很好理解，新加入一个新元素，维护 size++ 的同时，指针需要向后移动一位
    // 出队：当前 front 指向的元素从数组中移除，后一位元素就变成了队首，所以也需要向后移动一位
    // 这里之所以不说 ++，是因为循环队列里并不是单纯的 ++，而是 +1 后对 size 取余
    // 效果类似于 front = front (++%) data.length
    // data.length 是总容量，也就是总数，size 是当前量
    data[front] = null;
    front = (front + 1) % data.length;
    size --;

    // 并且如果出队以后元素不足 1/4，需要进行缩容操作
    if (size == getCapacity() / 4 && getCapacity() / 2 != 0) {
      resize(getCapacity() / 2);
    }

    return ret;
  }

  private void resize(int newCapacity) {
    E[] newData = (E[])new Object[newCapacity + 1];
    for (int i = 0; i < size; i++) {
      // 进行扩容时，front 所在的位置应该在新数组的首位，之后的每个元素都相对于 0 有 front 个元素的偏移
      // 需要对 data.length 进行取余操作来得到实际的元素角标位置：
      // 小于 length 的，取余后还是自身；大于 length 的，取余数后能绕回开头完成循环；
      newData[i] = data[(i + front) % data.length];
    }
    data = newData;
    // 完成扩容操作后，队首又变成了第一个元素，所以矫正一下 front 的指向
    front = 0;
    // 整个扩容操作不影响元素个数，所以 tail 的值还是与 size 相同的
    tail = size; 
  }

  @Override
  public String toString() {
    StringBuilder s = new StringBuilder();

    s.append("LoopQueue: front [");
    for (int i = front; i != tail; i = (i + 1) % data.length) {
      s.append(data[i]).append(String.format("(%s)", i));
      if ((i + 1) % data.length != tail) {
        s.append(", ");
      }
    }
    s.append("] end, size: " + size + ", capacity: " + getCapacity());

    return s.toString();
  }
  
}
