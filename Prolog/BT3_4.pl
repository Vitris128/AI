factorial(0, 1).
factorial(N, Result) :- N > 0,N1 is N - 1,factorial(N1, Result1),Result is N * Result1.
combination(N, 0, 1).
combination(N, K, Result) :- N >= K,factorial(N, FN),factorial(K, FK),NK is N - K,factorial(NK, FNK),Result is FN / (FK * FNK).
% combination(5, 2, X).
% combination(15, 4, X).