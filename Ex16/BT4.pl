thempt(L1, X, L2) :- append(L1, [X], L2).

% thempt([1,2,3,4],5,L2).
%  --> L2 = [1, 2, 3, 4, 5].

noids([],L,L).
noids([X1|L1],L2,[X1|L3]) :- noids(L1,L2,L3).

% noids([1,2,3],[a,b,c],Z).
% --> Z = [1, 2, 3, a, b, c].

ptvtle([], []).

ptvtle([X], [X]).
ptvtle([H, _ | T], [H | Result]) :- ptvtle(T, Result).

% ptvtle([2,4,3,1], L).
% --> L = [2, 3].


replace(I, [Old|T], [New|T], Old, New) :- I == 0, !.
replace(I, [H|T], [H|T1], Old, New) :- I > 0, I1 is I - 1, replace(I1, T, T1, Old, New).

swap(I, J, L1, L2) :-   replace(I, L1, L3, X, Y),
                        replace(J, L3, L2, Y, X).

% swap(1,5,[1,2,3,4,5,6,7,8],L2).
% --> L2 = [1, 6, 3, 4, 5, 2, 7, 8].



list_sum([],0).
list_sum([Head|Tail], Sum) :-   list_sum(Tail,SumTemp),
                                Sum is Head + SumTemp.

list_sum_odd(L, X):- ptvtle(L, L1), list_sum(L1,X).

% list_sum_odd([1,2,3,4,5],X).
% --> X = 9


less_than_X([], _, []).
less_than_X([H|T], N, X) :- H < N,
                            less_than_X(T, N, Z),
                            X = [H|Z].
less_than_X([H|T], N, X) :- H >= N,
                            less_than_X(T, N, X).

% less_than_X([1,2,3,4,5,6,7,8,9,10],5,X). 
% --> X = [1, 2, 3, 4]