delete3(_,[],[]).
delete3(X,[X|T],R):- delete3(X,T,R).
delete3(X,[H|T],[H|R]) :- delete3(X,T,R).
remove_duplicates([],[]).
remove_duplicates([H|T], [H|R]) :- member(H,T),!,delete3(H,T,R1),remove_duplicates(R1,R).
remove_duplicates([H|T],[H|R]):-remove_duplicates(T,R).