TP-Prolog 1

1. Thème de la généalogie

--A
parent(abdellatif,nabil).
parent(nabil,nour).
parent(jp, agathe).
parent(jm,jp).
parent(rene,didier).
parent(didier,adrien).
grand_parent(A,C):-parent(A,B),parent(B,C).

requetes
grand_parent(jm,agathe)
grand_parent(jm,A)

-> constante ne pas mettre de maj, variable mettre une maj

--B
ancetre(A,Z):-parent(A,Z).
ancetre(A,Z):-parent(B,Z),ancetre(A,B).

requetes
trace,ancetre(jm,nour).

-> 
call : test dun predicat
fail : le predicat est faux avec les conditions données
redo : quand il loupe la boucle et quil en refait une 
exit : il a trouvé une solution


--C

liste_des_ancetres([],_).
liste_des_ancetres([Head|Tail],Z):-
    ancetre(Head,Z),
    liste_des_ancetres(Tail,Z).

requetes
liste_des_ancetres([jm,jp],agathe) : true
->
toujours penser aux conditions de bord et aux conditions darret!

--D 

frere(X,Y):-parent(A,X),parent(A,Y).

requetes : frere(agathe,victor) : true
-> pas de "il existe" mais langage assez permissif-non permissif


--E 

cousin(X,Y):-parent(A,X),parent(B,Y),frere(A,B).

requetes
cousin(agathe,camille)



--- code total
parent(abdellatif,nabil).
parent(nabil,nour).
parent(jp, agathe).
parent(jp, victor).
parent(jm,jp).
parent(rene,didier).
parent(didier,adrien).
parent(helene,camille).
parent(jm,helene).
ma_liste([jm,jp]).
grand_parent(A,C):-parent(A,B),parent(B,C).
ancetre(A,Z):-parent(A,Z).
ancetre(A,Z):-parent(B,Z),ancetre(A,B).
liste_des_ancetres([],_).
liste_des_ancetres([Head|Tail],Z):-
    ancetre(Head,Z),
    liste_des_ancetres(Tail,Z).
frere(X,Y):-parent(A,X),parent(A,Y).
cousin(X,Y):-parent(A,X),parent(B,Y),frere(A,B).



2. Manipulation de listes

-- A

ma_liste([1,2,3,4,5]).
membre(X,[X|_]).
membre(X,[_|L]) :- membre(X,L).
concat([],L,L).
concat([X1|L1],L2,[X1|L3]):-concat(L1,L2,L3).

requetes
concat([1,2],[3,4],L).

--B 
dernier([X],X).
dernier( [_| Tail], X) :- dernier(Tail, X).

--C
element(_, [], []).
element(X,[X|Tail],L) :- element(X,Tail,L).
element(X, [Y|Tail], [Y|L]) :- 
    Y \= X,
    element(X, Tail, L).

--D 
inv([],[]).
inv([T|Q],R) :- inv(Q,R1), concat(R1,[T],R

-> tests pas faits

--E 
composante(1,Head,[Head|_]).
composante(I,X,[_|Tail]) :- composante(J,X,Tail), I is J+1.

--F 
subsAll(_,_,[],[]).
subsAll(X,Y,[X | Tail],[Y | NewTail]) :- subsAll(X, Y, Tail, NewTail).
subsAll(X,Y,[Head | Tail],[Head | NewTail]) :- 
    Head \= X,
    subsAll(X, Y, Tail, NewTail).


--G 
membre(X,[X|_]).
membre(X,[_|L]) :- membre(X,L).
concat([],L,L).
concat([X1|L1],L2,[X1|L3]):-concat(L1,L2,L3).

list2ens([],[]).
list2ens([Head | Tail], Set) :- \+membre(Head,Set),concat(Head,Set,SetBis),list2ens(Tail,SetBis).

setify([], []).
setify([Head|Tail] , Set) :- 
    membre(Head, Tail),
    setify(Tail, Set).
setify([Head|Tail] , [Head|Set]) :-
    \+ membre(Head, Tail),
    setify(Tail, Set).