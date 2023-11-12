male(james_i).
male(james_ii).
male(charle_i).
male(charle_ii).
male(george_i).

female(catherine).
female(elizabeth).
female(sophia).

parent(james_i, charle_i).
parent(james_i, elizabeth).

parent(charle_i, catherine).
parent(charle_i, charle_ii).
parent(charle_i, james_ii).

parent(elizabeth, sophia).

parent(sophia, george_i).

/**
parent(george_i, charle_i).
parent(X, charle_i).
parent(charle_i, X).
*/

mother(M,X) :- parent(M,X), female(M).

father(F,X) :- parent(F,X), male(F).

sibling(X,Y) :- parent(Z,X), parent(Z,Y).