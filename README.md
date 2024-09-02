# RMQ
This code implement [Range Minimum Query](https://en.wikipedia.org/wiki/Range_minimum_query) problem solving.

This code have 4 variations for solving the problem.

*V1* - No preprocessing - takes linear run time to answer a query.

*V2* - O(n^2^) preprocessing run time. Find the minimum in all the possible ranges and store them in O(n^2^) memory space. 
Takes constant run time to answer a query.

*V3* - O(n) preprocessing run time. Find the minimum in O( $\sqrt{n}$ )  ranges in O(n) memory space.
Takes O(n^1.5^) run time to answer a query.

*V4* - O(nlog(n)) preprocessing run time. Find the minimum in ranges in length of powers of 2 from every index 
and store them in O(nlog(n)) memory space. Takes constant run time to answer a query.

Read more at [Stanford CS166 RMQ introduction slides](https://web.stanford.edu/class/archive/cs/cs166/cs166.1146/lectures/00/Small00.pdf)
