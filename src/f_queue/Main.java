package src.f_queue;

import src.f_queue.quiz.LoopQueue3;
import src.utils.ArrayGenerator;
import src.f_queue.quiz.QueueByStack;

public class Main {

  public static void main(String[] args) {
    testLoopQueue();
    testQueueByStack();
  }

  public static void testLoopQueue() {
    ArrayQueue<Integer> arrayQueue = new ArrayQueue<>();
    // LoopQueue<Integer> loopQueue = new LoopQueue<>();
    // LoopQueue2<Integer> loopQueue = new LoopQueue2<>();
    LoopQueue3<Integer> loopQueue = new LoopQueue3<>();

    int[] dataSize = new int[]{ 10000 };

    for (int n : dataSize) {
      Integer[] randomArray = ArrayGenerator.generateRandomArray(n);
      for (int i = 0; i < n; i++) {
        arrayQueue.enqueue(randomArray[i]);
        loopQueue.enqueue(randomArray[i]);
      }

      double startTime = System.nanoTime();
      for (int i = 0; i < n; i++) {
        arrayQueue.dequeue();
      }
      double endTime = System.nanoTime();
      double time1 = (endTime - startTime) / 1000000000.0;

      startTime = System.nanoTime();
      for (int i = 0; i < n; i++) {
        loopQueue.dequeue();
      }
      endTime = System.nanoTime();
      double time2 = (endTime - startTime) / 1000000000.0;

      System.out.println("ArrayQueue, time: " + time1 + " s");
      System.out.println("LoopQueue, time: " + time2 + " s");
    }
  }

  public static void testQueueByStack() {
    QueueByStack<Integer> queueByStack = new QueueByStack<>();
    for (int i = 0; i < 10; i++) {
      queueByStack.enqueue(i);
      System.out.println(queueByStack);
      if (i % 3 == 2) {
        queueByStack.dequeue();
        System.out.println(queueByStack);
      }
    }
  }
  
}
