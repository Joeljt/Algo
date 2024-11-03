package src.c_array;

public class Main {
  
  public static void main(String[] args) {
    
    Array<Integer> array = new Array<>(10);
    for (int i = 0; i < 10; i++) {
      array.addLast(i);
    }
    System.out.println(array); 

    array.add(1, 100);
    System.out.println(array); 

    array.addFirst(-1);
    System.out.println(array); 

    array.remove(2);
    System.out.println(array); 

    array.removeElement(4);
    System.out.println(array); 

    // array.removeFirst();
    array.removeLast();
    System.out.println(array); 


    // Array<Student> arr = new Array<Student>();

    // arr.addLast(new Student("Joseph Lee", "29"));
    // arr.addLast(new Student("Chandler Bing", "29"));
    // arr.addLast(new Student("Ross Geller", "29"));

    // System.out.println(arr);

  }

}
