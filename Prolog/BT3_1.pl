power(_, 0, 1).
power(X, Y, Z) :- Y > 0,Y1 is Y - 1,power(X, Y1, Z1),Z is X * Z1.

% power(5,2,X).