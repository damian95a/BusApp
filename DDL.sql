CREATE SCHEMA proj_mpk;

CREATE TABLE proj_mpk.kierowca(
    "id" BIGINT NOT NULL,
    "imie" VARCHAR(255) NOT NULL,
    "nazwisko" VARCHAR(255) NOT NULL,
    "uprawnienia_przegubowe" BOOLEAN NOT NULL
);
ALTER TABLE proj_mpk.kierowca ADD PRIMARY KEY("id");

CREATE TABLE proj_mpk.autobus(
    "id_autobus" BIGINT NOT NULL,
    "pojemnosc" BIGINT NOT NULL,
    "przegubowy" BOOLEAN NOT NULL,
    "naped" VARCHAR(255) NOT NULL
);
ALTER TABLE proj_mpk.autobus ADD PRIMARY KEY("id_autobus");

CREATE TABLE proj_mpk.kurs(
    "id_kurs" BIGSERIAL NOT NULL,
    "id_kierowca_autobus" BIGINT NOT NULL,
    "godzina_odjazd" TIME(0) WITHOUT TIME ZONE NOT NULL,
    "godzina_przyjazd" TIME(0) WITHOUT TIME ZONE NOT NULL,
    "numer_linii" BIGINT NOT NULL,
    "powrot" BOOLEAN NOT NULL
);
ALTER TABLE proj_mpk.kurs ADD PRIMARY KEY("id_kurs");

CREATE TABLE proj_mpk.linia(
    "numer_linii" BIGINT NOT NULL,
    "kierunek" VARCHAR(255) NOT NULL,
    "kierunek_powrotny" VARCHAR(255) NOT NULL
);
ALTER TABLE proj_mpk.linia ADD PRIMARY KEY("numer_linii");

CREATE TABLE proj_mpk.przystanek(
    "id" BIGSERIAL NOT NULL,
    "nazwa" VARCHAR(255) NOT NULL
);
ALTER TABLE proj_mpk.przystanek ADD PRIMARY KEY("id");
ALTER TABLE
    proj_mpk.przystanek ADD CONSTRAINT "przystanek_nazwa_unique" UNIQUE("nazwa");

CREATE TABLE proj_mpk.przystanek_linia(
    "id" BIGSERIAL NOT NULL,
    "id_przystanek" BIGINT NOT NULL,
    "numer_linii" BIGINT NOT NULL,
    "czas_dojazdu" BIGINT NOT NULL,
    "kolejnosc" BIGINT NOT NULL
);
ALTER TABLE proj_mpk.przystanek_linia ADD PRIMARY KEY("id");

CREATE TABLE proj_mpk.kierowca_autobus(
    "id" BIGSERIAL NOT NULL,
    "id_kierowca" BIGINT NOT NULL,
    "id_autobus" BIGINT NOT NULL
);
ALTER TABLE proj_mpk.kierowca_autobus ADD PRIMARY KEY("id");

CREATE SCHEMA logowanie;
CREATE TABLE logowanie.kierowca(
    "login" VARCHAR(100) NOT NULL,
    "haslo" VARCHAR(100) NOT NULL
);
ALTER TABLE logowanie.kierowca ADD PRIMARY KEY("login");

CREATE TABLE logowanie.czlonek_zarzadu(
    "login" VARCHAR(100) NOT NULL,
    "haslo" VARCHAR(100) NOT NULL
);
ALTER TABLE logowanie.czlonek_zarzadu ADD PRIMARY KEY("login");

ALTER TABLE
    proj_mpk.kierowca_autobus ADD CONSTRAINT "kierowca_autobus_id_autobus_foreign" FOREIGN KEY("id_autobus") REFERENCES proj_mpk.autobus("id_autobus");
ALTER TABLE
    proj_mpk.przystanek_linia ADD CONSTRAINT "przystanek_linia_id_przystanek_foreign" FOREIGN KEY("id_przystanek") REFERENCES proj_mpk.przystanek("id");
ALTER TABLE
    proj_mpk.przystanek_linia ADD CONSTRAINT "przystanek_linia_numer_linii_foreign" FOREIGN KEY("numer_linii") REFERENCES proj_mpk.linia("numer_linii");
ALTER TABLE
    proj_mpk.kurs ADD CONSTRAINT "kurs_numer_linii_foreign" FOREIGN KEY("numer_linii") REFERENCES proj_mpk.linia("numer_linii");
ALTER TABLE
    proj_mpk.kurs ADD CONSTRAINT "kurs_id_kierowca_autobus_foreign" FOREIGN KEY("id_kierowca_autobus") REFERENCES proj_mpk.kierowca_autobus("id");
ALTER TABLE
    proj_mpk.kierowca_autobus ADD CONSTRAINT "kierowca_autobus_id_kierowca_foreign" FOREIGN KEY("id_kierowca") REFERENCES proj_mpk.kierowca("id");


CREATE OR REPLACE FUNCTION proj_mpk.przystanek_duplikat()
RETURNS TRIGGER 
LANGUAGE plpgsql
AS 
$$
BEGIN
    IF NEW.id_przystanek in (SELECT id_przystanek FROM proj_mpk.przystanek_linia WHERE numer_linii=NEW.numer_linii) THEN
        RAISE EXCEPTION 'Nie można kolejny raz przypisać przystanku do linii.';
    END IF;

    IF NEW.kolejnosc in (SELECT kolejnosc FROM proj_mpk.przystanek_linia WHERE numer_linii=NEW.numer_linii) THEN
        RAISE EXCEPTION 'Dwa przystanki na linii nie mogą mieć tej samej pozycji w kolejności.';
    END IF;

    RETURN NEW;
END
$$;

CREATE TRIGGER przystanek_bez_duplikatow
    BEFORE INSERT ON proj_mpk.przystanek_linia
    FOR EACH ROW EXECUTE PROCEDURE proj_mpk.przystanek_duplikat();


CREATE OR REPLACE FUNCTION proj_mpk.kierowca_uprawnienia()
RETURNS TRIGGER 
LANGUAGE plpgsql
AS 
$$
BEGIN
    IF (SELECT przegubowy FROM proj_mpk.autobus WHERE id_autobus=NEW.id_autobus)
        AND NOT (SELECT uprawnienia_przegubowe FROM proj_mpk.kierowca WHERE id=NEW.id_kierowca) THEN
        RAISE EXCEPTION 'Kierowca % nie ma uprawnień, by kierować autobuem przegubowym.',NEW.id_kierowca;
    END IF;

    RETURN NEW;
END
$$;

CREATE TRIGGER uprawnienia_przegub
    BEFORE INSERT ON proj_mpk.kierowca_autobus
    FOR EACH ROW EXECUTE PROCEDURE proj_mpk.kierowca_uprawnienia();

CREATE VIEW czas_przejazdu(linia, czas) AS
    SELECT numer_linii, SUM(czas_dojazdu) FROM proj_mpk.przystanek_linia
    GROUP BY numer_linii;

CREATE VIEW godziny_autobus(id_autobus, odj, przyj) AS
    SELECT A.id_autobus, godzina_odjazd, godzina_przyjazd FROM proj_mpk.kurs K
    JOIN proj_mpk.kierowca_autobus KA ON KA.id=K.id_kierowca_autobus
    JOIN proj_mpk.autobus A USING(id_autobus);

CREATE VIEW godziny_kierowca(id_kierowca, odj, przyj) AS
    SELECT Ki.id, godzina_odjazd, godzina_przyjazd FROM proj_mpk.kurs K
    JOIN proj_mpk.kierowca_autobus KA ON KA.id=K.id_kierowca_autobus
    JOIN proj_mpk.kierowca Ki ON Ki.id=KA.id_kierowca;

CREATE OR REPLACE FUNCTION id_kierowcy(BIGINT)
RETURNS BIGINT
LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN (SELECT id_kierowca FROM proj_mpk.kierowca_autobus WHERE id=$1);
END
$$;

CREATE OR REPLACE FUNCTION id_autobusu(BIGINT)
RETURNS BIGINT
LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN (SELECT id_autobus FROM proj_mpk.kierowca_autobus WHERE id=$1);
END
$$;

CREATE OR REPLACE FUNCTION proj_mpk.godziny_kursu_i_kolizje()
RETURNS TRIGGER 
LANGUAGE plpgsql
AS 
$$
BEGIN
    NEW.godzina_przyjazd := NEW.godzina_odjazd + '1 minute'::interval*(SELECT czas FROM czas_przejazdu WHERE linia=NEW.numer_linii);

    IF (SELECT COUNT(*) FROM (
            (SELECT * FROM godziny_autobus WHERE odj<=NEW.godzina_odjazd AND NEW.godzina_odjazd<=przyj AND id_autobus=id_autobusu(NEW.id_kierowca_autobus))
            UNION
            (SELECT * FROM godziny_autobus WHERE odj<=NEW.godzina_przyjazd AND NEW.godzina_przyjazd<=przyj AND id_autobus=id_autobusu(NEW.id_kierowca_autobus))
        ) AS HA) >0 THEN
            RAISE EXCEPTION 'Autobus nr % jest już w tym czasie zajęty.',
            id_autobusu(NEW.id_kierowca_autobus);
    END IF;

    IF (SELECT COUNT(*) FROM (
            (SELECT * FROM godziny_kierowca WHERE odj<=NEW.godzina_odjazd AND NEW.godzina_odjazd<=przyj AND id_kierowca=id_kierowcy(NEW.id_kierowca_autobus))
            UNION
            (SELECT * FROM godziny_kierowca WHERE odj<=NEW.godzina_przyjazd AND NEW.godzina_przyjazd<=przyj AND id_kierowca=id_kierowcy(NEW.id_kierowca_autobus))
        ) AS HK) >0 THEN
            RAISE EXCEPTION 'Kierowca nr % jest już w tym czasie zajęty.',
            id_kierowcy(NEW.id_kierowca_autobus);
    END IF;


    RETURN NEW;
END
$$;

CREATE TRIGGER kurs_wstaw_czas
    BEFORE INSERT ON proj_mpk.kurs
    FOR EACH ROW EXECUTE PROCEDURE proj_mpk.godziny_kursu_i_kolizje();


CREATE OR REPLACE FUNCTION proj_mpk.czas_jazdy(id_p BIGINT, st TIME(0), id_l BIGINT)
RETURNS TIME(0)
LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN (st + '1 minute'::interval*(SELECT SUM(czas_dojazdu) FROM proj_mpk.przystanek_linia
    WHERE numer_linii=id_l AND kolejnosc<=id_p
    GROUP BY numer_linii));
END
$$;

CREATE OR REPLACE FUNCTION proj_mpk.czas_jazdy_powrot(id_p BIGINT, st TIME(0), id_l BIGINT)
RETURNS TIME(0)
LANGUAGE plpgsql
AS
$$
BEGIN
    IF id_p=(SELECT MAX(kolejnosc) FROM proj_mpk.przystanek_linia
        WHERE numer_linii=id_l GROUP BY numer_linii)
    THEN
        RETURN st;
    ELSE
            RETURN (st + '1 minute'::interval*(SELECT SUM(czas_dojazdu) FROM proj_mpk.przystanek_linia
            WHERE numer_linii=id_l AND kolejnosc>id_p
            GROUP BY numer_linii));
    END IF;
END
$$;

CREATE OR REPLACE FUNCTION proj_mpk.czas_jazdy_uniwersalny(id_p BIGINT, st TIME(0), id_l BIGINT, p BOOLEAN)
RETURNS TIME(0)
LANGUAGE plpgsql
AS
$$
BEGIN
    IF p THEN
        RETURN proj_mpk.czas_jazdy_powrot((SELECT kolejnosc FROM proj_mpk.przystanek_linia WHERE numer_linii=id_l AND id_przystanek=id_p),st,id_l);
    ELSE
            RETURN proj_mpk.czas_jazdy((SELECT kolejnosc FROM proj_mpk.przystanek_linia WHERE numer_linii=id_l AND id_przystanek=id_p),st,id_l);
    END IF;
END
$$;


CREATE OR REPLACE FUNCTION proj_mpk.kol_przyst(id_p BIGINT, id_l BIGINT)
RETURNS BIGINT
LANGUAGE plpgsql
AS
$$
BEGIN
    RETURN (SELECT kolejnosc FROM proj_mpk.przystanek_linia
            WHERE id_przystanek=id_p AND numer_linii=id_l);
END
$$;

CREATE OR REPLACE FUNCTION proj_mpk.trasa(przyst1 BIGINT, przyst2 BIGINT)
RETURNS TABLE (id_autobus BIGINT, id_kurs BIGINT, numer_linii BIGINT, t1 TIME(0), t2 TIME(0))
AS
$$
BEGIN
    RETURN QUERY
    SELECT * FROM (
        SELECT KA.id_autobus, K.id_kurs, K.numer_linii, proj_mpk.czas_jazdy_uniwersalny(przyst1,K.godzina_odjazd, K.numer_linii,K.powrot) AS p1, proj_mpk.czas_jazdy_uniwersalny(przyst2,K.godzina_odjazd, K.numer_linii,K.powrot) AS p2
        FROM proj_mpk.kierowca_autobus KA
        JOIN proj_mpk.kurs K ON K.id_kierowca_autobus=KA.id) AS PST
    WHERE p1 IS NOT NULL AND p2 IS NOT NULL AND p2>p1;
END
$$
LANGUAGE plpgsql;