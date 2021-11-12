DROP TABLE contacts;
DROP TABLE interactions;
DROP TABLE tags;
DROP TABLE history_contact;
DROP TABLE history_interaction;
DROP TABLE history_global;


CREATE TABLE IF NOT EXISTS contacts (
    id INTEGER PRIMARY KEY,
    email TEXT,
    first_name TEXT NOT NULL,
    last_name TEXT NOT NULL,
    enterprise TEXT,
    phone TEXT,
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
    name TEXT NOT NULL,
    id_contact INTEGER NOT NULL,
    id_interaction INTEGER NOT NULL,
    PRIMARY KEY (id_contact, id_interaction)
    FOREIGN KEY (id_interaction)
      REFERENCES interactions (id_interaction)
      ON DELETE CASCADE
    FOREIGN KEY (id_contact)
      REFERENCES contacts (id)
      ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS history_global (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    contenue TEXT NOT NULL,
    dt TEXT
);

CREATE TABLE IF NOT EXISTS history_contact (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    id_contact INTEGER,
    contenue TEXT NOT NULL,
    dt TEXT,
    FOREIGN KEY (id_contact)
      REFERENCES contacts (id)
      ON DELETE CASCADE
);

CREATE TABLE IF NOT EXISTS history_interaction (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    id_contact INTEGER,
    id_interaction INTEGER,
    contenue TEXT NOT NULL,
    dt TEXT,
    FOREIGN KEY (id_contact)
      REFERENCES contacts (id)
      ON DELETE CASCADE
    FOREIGN KEY (id_interaction)
      REFERENCES interactions (id_interaction)
      ON DELETE CASCADE
);
