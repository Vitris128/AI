count(_, [], 0) :- !.
count(X, [X|T], N) :- count(X, T, N1), N is N1 + 1, !.
count(X, [_|T], N) :- count(X, T, N).