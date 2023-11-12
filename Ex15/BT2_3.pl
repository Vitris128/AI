% Anh ruột, chị ruột, em trai ruột, em gái ruột
anh_ruot(X, Y) :- nam(X), cha(Z, X), cha(Z, Y), khac(X, Y).
chi_ruot(X, Y) :- nu(X), cha(Z, X), cha(Z, Y), khac(X, Y).
em_trai_ruot(X, Y) :- nam(X), cha(Z, Y), cha(Z, X), khac(X, Y).
em_gai_ruot(X, Y) :- nu(X), cha(Z, Y), cha(Z, X), khac(X, Y).

% Chú, Bác trai, Cậu
chu(X, Y) :- cha(Z, Y), anh_hoac_chi(Z, X).
bac_trai(X, Y) :- cha(Z, Y), em_hoac_de(X, Z), nam(X).
cau(X, Y) :- cha(Z, Y), em_hoac_de(X, Z), nam(X).

% Cô, Dì, Mợ, Thím, Bác gái
co(X, Y) :- cha(Z, Y), chi_ruot(X, Z).
di(X, Y) :- cha(Z, Y), em_gai_ruot(X, Z).
mo(X, Y) :- cha(Z, Y), chi_ruot(X, Z).
thim(X, Y) :- cha(Z, Y), em_gai_ruot(X, Z).
bac_gai(X, Y) :- cha(Z, Y), em_gai_ruot(X, Z).

% Ông nội, ông ngoại
ong_noi(X, Y) :- cha(Z, Y), cha(X, Z), nam(X).
ong_ngoai(X, Y) :- cha(Z, Y), me(X, Z), nam(X).

% Bà nội, bà ngoại
ba_noi(X, Y) :- me(Z, Y), cha(X, Z), nu(X).
ba_ngoai(X, Y) :- me(Z, Y), me(X, Z), nu(X).

% Cha vợ, mẹ vợ, cha chồng, mẹ chồng
cha_vo(X, Y) :- vo(Y, Z), cha(X, Z).
me_vo(X, Y) :- vo(Y, Z), me(X, Z).
cha_chong(X, Y) :- chong(Y, Z), cha(X, Z).
me_chong(X, Y) :- chong(Y, Z), me(X, Z).


% Quy tắc giúp kiểm tra hai người có khác nhau không
khac(X, Y) :- X \= Y.



% nam(a).
% nam(b).
% nam(father).
% nu(mother).
% cha(father, a).
% cha(father, b).
% me(mother, a).
% me(mother, b).
% cha(X,Y).
% me(X,Y).
% anh_ruot(X,Y).