set([], []) :- !.
set([H|T], [H|T1]) :- subtract(T, [H], T2), set(T2, T1).