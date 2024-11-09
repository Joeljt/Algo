package src.e_stack.quiz;

import java.util.Stack;
import java.util.Map;
import java.util.HashMap;
import java.util.Deque;
import java.util.LinkedList;

public class Parenthesis {

     public static boolean isValidParenthesis(String input) {
        Stack<Character> stack = new Stack<>();
        for (int i = 0; i < input.length(); i++) {
            char e = input.charAt(i);
            if (e == '(' || e == '{' || e == '[') {
                stack.push(e);
            } else {
                if (stack.isEmpty()) return false;
                char top = stack.pop();
                if (e == ')' && top != '(') return false;
                if (e == ']' && top != '[') return false;
                if (e == '}' && top != '{') return false;
            }
        }
        return stack.isEmpty();
    }

    public static boolean isValidParenthesis2(String s) {
        if(s.length() % 2 != 0) return false; 

        Stack<Character> stack = new Stack<>();

        for(int i = 0;i<s.length();i++){
                char c = s.charAt(i);
            if(c == '(') stack.push(')');
            else if(c == '[') stack.push(']');
            else if(c == '{') stack.push('}');
            else if(stack.isEmpty() || stack.peek() != c) return false;
            else stack.pop();
    }

        return stack.isEmpty();
    }

    public static boolean isValid(String s) {
        int n = s.length();
        if (n % 2 == 1) return false;

        Map<Character, Character> pairs = new HashMap<Character, Character>() {{
            put(')', '(');
            put(']', '[');
            put('}', '{');
        }};
        Deque<Character> stack = new LinkedList<Character>();
        for (int i = 0; i < n; i++) {
            char ch = s.charAt(i);
            if (pairs.containsKey(ch)) {
                if (stack.isEmpty() || stack.peek() != pairs.get(ch)) {
                    return false;
                }
                stack.pop();
            } else {
                stack.push(ch);
            }
        }
        return stack.isEmpty();
    }
    
}
