package src.f_queue;

import src.utils.ArrayGenerator;

public class Main {

  public static void main(String[] args) {

    // LoopQueueNoSize<Integer> loopQueue = new LoopQueueNoSize<>();
    // loopQueue.enqueue(1);
    // loopQueue.enqueue(2);
    // loopQueue.enqueue(3);
    // loopQueue.enqueue(4);
    // System.out.println(loopQueue);

    // loopQueue.dequeue();
    // loopQueue.dequeue();
    // System.out.println(loopQueue);

    // Integer[] randomArray = ArrayGenerator.generateRandomArray(10);
    //   for (int i = 0; i < 10; i++) {
    //     loopQueue.enqueue(randomArray[i]);
    //   }
    //   System.out.println(loopQueue);

    //   double startTime = System.nanoTime();
    //   for (int i = 0; i < 10; i++) {
    //     loopQueue.dequeue();
    //   }
    //   double endTime = System.nanoTime();
    //   double time1 = (endTime - startTime) / 1000000000.0;
    //   System.out.println("LoopQueueNoSize, time: " + time1 + " s");

    ArrayQueue<Integer> arrayQueue = new ArrayQueue<>();
    LoopQueueNoSize<Integer> loopQueue = new LoopQueueNoSize<>();

    int[] dataSize = new int[]{ 100000 };

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
  
}
