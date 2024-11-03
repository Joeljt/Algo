package src.c_array;
public class Student {
  
  private String name;
  private String age;

  public Student(String name, String age) {
    this.name = name;
    this.age = age;
  }

  @Override
  public String toString() {
    return String.format("Student[%s] - %s", name, age);
  }
}
