man(marcus).
pompeian(marcus).
roman(X):-pompeian(X).
ruler(ceasar).
assasinate(X,Y):- roman(X), notloyalto(X, Y), ruler(Y).
notloyalto(marcus,ceasar).

% assasinate(marcus,ceasar).
% roman(X).
% ruler(X).
% assasinate(X,Y).