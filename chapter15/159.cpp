//
// Created by yel on 2021/2/26.
//

// Text Queries Revisited

// As an example of inheritance, we'll extend our text-query application from 12.3.
// which let us look for occurrences of a given word in life.
// the file is shown in test_files/159

// our system should support the following queries:
// 1. Word queries find all the lines that match a given string:
// Executing Query for:
// Daddy Daddy occurs 3 times
// (line 2) Her Daddy says when the wind blows

// 2. Not queries, using the ~ operator, yield lines that don't match the query
// ~(Alice) occurs 9 times
// (line 2) Her Daddy says when the wind blows

// 3. Or queries, using the | operator, return lines matching either of two queries:
// Executing Query for: (hair | Alice)
// (hair | Alice) occurs 2 times

// 4. And queries, using the & operator, return lines matching both queries:
// Executing query for: (hair & Alice)
// (hair & Alice) occurs 1 time

// Moreover, we want to be able to combine these operations, as in
// fiery & bird | wind:
// Executing Query for: ((fiery & bird) | wind)
// ((fiery & bird) | wind) occurs 3 times
// (line 2) Her Daddy says when the wind blows

// 159.1 An object-oriented solution



