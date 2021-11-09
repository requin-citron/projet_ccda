DROP TABLE contacts;
DROP TABLE interactions;
DROP TABLE tags;
DROP TABLE history_contact;
DROP TABLE history_interaction;

CREATE TABLE IF NOT EXISTS contacts (
    id INTEGER PRIMARY KEY,
    email TEXT,
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL,
    enterprise TEXT,
    phone INTEGER,
    photo TEXT
);

CREATE TABLE IF NOT EXISTS interactions (
    id_contact INTEGER NOT NULL,
    id_interaction INTEGER NOT NULL,
    contenue TEXT NOT NULL,
    PRIMARY KEY (id_contact, id_interaction)
    FOREIGN KEY (id_contact)
      REFERENCES contacts (id)
      ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS tags (
    name TEXT PRIMARY KEY,
    id_interaction TEXT NOT NULL,
    FOREIGN KEY (id_interaction)
      REFERENCES interactions (id_interaction)
      ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS history_contact (
    id_contact INTEGER PRIMARY KEY,
    contenue TEXT NOT NULL,
    dt datetime default current_timestamp,
    FOREIGN KEY (id_contact)
      REFERENCES contacts (id)
      ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS history_interaction (
    id_contact INTEGER,
    id_interaction INTEGER,
    contenue TEXT NOT NULL,
    dt datetime default current_timestamp,
    PRIMARY KEY (id_contact, id_interaction)
    FOREIGN KEY (id_contact)
      REFERENCES contacts (id)
      ON DELETE CASCADE
);
