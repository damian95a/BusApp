SET SEARCH_PATH TO proj_mpk;

INSERT INTO przystanek (nazwa)
VALUES ('Muzeum'),
('AGH'),
('Kleparz'),
('Dworzec'),
('Politechnika'),
('UJ'),
('Wawel');

INSERT INTO linia (numer_linii, kierunek, kierunek_powrotny)
VALUES (101, 'Dworzec', 'Muzeum'),
(192, 'Dworzec', 'Wawel'),
(201, 'Wawel', 'Muzeum');

INSERT INTO przystanek_linia (id_przystanek, numer_linii, czas_dojazdu, kolejnosc)
VALUES (1,101, 0, 1),
(2,101, 2, 2),
(5,101, 7, 3),
(4,101, 2, 4),

(7,192, 0, 1),
(6,192, 4, 2),
(5,192, 6, 3),
(4,192, 2, 4),

(7,201, 0, 1),
(4,201, 10, 2),
(1,201, 10, 3);

INSERT INTO kierowca (id, imie, nazwisko, uprawnienia_przegubowe)
VALUES (1, 'Adam', 'Nowak', 'true'),
(2, 'Kamil', 'Kowalski', 'true'),
(3, 'Andrzej', 'Wójcik', 'false');

INSERT INTO autobus (id_autobus, pojemnosc, przegubowy, naped)
VALUES (1, 120, 'true', 'elektryczny'),
(2, 120, 'true', 'spalinowy'),
(3, 50, 'false', 'spalinowy');

INSERT INTO kierowca_autobus (id_kierowca, id_autobus)
VALUES (1,1), (2,2), (3,3), (2,3);

INSERT INTO kurs (id_kierowca_autobus, godzina_odjazd, numer_linii, powrot)
VALUES (1, '10:00', 101, 'false'),
(1, '10:20', 101, 'true'),
(2, '10:05', 101, 'false'),
(2, '10:30', 101, 'true'),

(3, '11:00', 192, 'false'),

(4, '12:00', 201, 'false');


INSERT INTO logowanie.kierowca (login, haslo)
VALUES ('kierowca1','123'), ('kierowca2','abc');

INSERT INTO logowanie.czlonek_zarzadu (login, haslo)
VALUES ('admin', 'admin');