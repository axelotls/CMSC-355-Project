# Bank Customer System

This program is capable of searching, creating, and displaying bank customers created within the runtime. System questions are displayed in the terminal and user responses correlate to our various use-case paths. User inputs are verified for enhanced security.

Customer.java holds get-set functions and Banker.java allows for the creation, management, and verification of Customer objects. A customer consists of a valid first and last name, date of birth, and Social Security Number. Our Main function consists of Bank system questions correlating to our predetermined use-cases

The majority of our programming difficulties came from string validation, particularly validating names, DOB, and SSN. However, those difficulties were resolved after implementing _Patterns.matches_ from RegEx. One overall barrier of our system is the lack of data management. Customers can be created, displayed, and searched within the program but any changes made are not saved outside of runtime. In the future, we intend to create an external logging system.

+ To clean working directory: 
    run ```rm $(find . -name "*.class")```

+ To compile Project: 
    run ```javac Customer.java Banker.java``` 

+ To run project: 
    run ```java Banker```
