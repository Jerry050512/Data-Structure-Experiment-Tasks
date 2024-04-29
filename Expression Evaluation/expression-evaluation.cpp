#include <iostream>
#include <iomanip>
#include <string>
#include <cctype>
#include <unordered_map>
#include "stack.cpp"

using namespace std;

unordered_map<char, int> op_precedence = {
    {'+', 1},
    {'-', 1},
    {'*', 2},
    {'/', 2},
    {'%', 2}
};

double apply_operation(double a, double b, char op)
{
    switch (op)
    {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    case '/':
        return a / b;
    // case '%':
    //     return a % b;
    }
    return 0; // Should never reach here
}

double evaluate_expression(string expression)
{
    Stack<double> values; // Stack to store operands
    Stack<char> ops;   // Stack to store operators

    bool prev_was_digit = false;
    double multiple = 10;
    for (char c : expression)
    {
        if (isdigit(c))
        {
            if(prev_was_digit)
            {
                // Check if need cancatenate the digit to the previous digit
                if(multiple > 1)
                {
                    values.top() = values.top() * multiple + (c - '0');
                }
                else
                {
                    values.top() = values.top() + (c - '0') * multiple;
                    multiple /= 10;
                }
            }
            else
            {
                // The start of a number
                values.push(c - '0'); // Push the operand onto the values stack
                prev_was_digit = true;
                multiple = 10;
            }
        }
        else if (c == '.')
        {
            multiple = .1;
            // Handle float number started with .
            if(!prev_was_digit)
                values.push(0);
            prev_was_digit = true;
        }
        else if (c == '(')
        {
            ops.push(c); // Push the opening parenthesis onto the ops stack
            prev_was_digit = false;
        }
        else if (c == ')')
        {
            // Evaluate the sub-expression inside the parentheses
            while (!ops.isEmpty() && ops.top() != '(')
            {
                double b = values.pop();
                double a = values.pop();
                char op = ops.pop();
                values.push(apply_operation(a, b, op));
            }
            if (!ops.isEmpty())
            {
                ops.pop(); // Pop the opening parenthesis from the ops stack
            }
            prev_was_digit = false;
        }
        else if (op_precedence.count(c))
        {
            // Process the operator
            while (!ops.isEmpty() && op_precedence.count(ops.top()) && op_precedence[ops.top()] >= op_precedence[c])
            {
                double b = values.pop();
                double a = values.pop();
                char op = ops.pop();
                values.push(apply_operation(a, b, op));
            }
            ops.push(c); // Push the current operator onto the ops stack
            prev_was_digit = false;
        }
    }

    // Evaluate any remaining operators
    while (!ops.isEmpty())
    {
        double b = values.pop();
        double a = values.pop();
        char op = ops.pop();
        values.push(apply_operation(a, b, op));
    }

    return values.pop(); // The final result is on the top of the values stack
}

int main()
{
    string expression;
    cout << "Enter multiline expression endswith '=' unknown operator will be skip: \n";
    while(true)
    {
        getline(cin, expression);
        if(expression == string("="))
        {
            break;
        }

        double result = evaluate_expression(expression);
        cout << expression << " " << fixed << setprecision(2) << result << endl;
    }
    cout << "Program exited" << endl;

    return 0;
}