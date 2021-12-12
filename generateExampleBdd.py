#!/bin/python3

import requests
import bs4
import sqlite3

def generate_contact():
    headers = {
        'authority': 'fr.fakenamegenerator.com',
        'user-agent': 'chevalo',
        'accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.9',
        'referer': 'https://fr.fakenamegenerator.com/gen-random-fr-fr.php',
        'accept-language': 'fr-FR,fr;q=0.9,en-US;q=0.8,en;q=0.7',
    }

    response = requests.get('https://fr.fakenamegenerator.com/gen-random-fr-fr.php', headers=headers)
    contact = bs4.BeautifulSoup(response.text, "html.parser").find_all("div",{"class":"info"})[0]
    ret = {}
    ret["firstname"], ret["lastname"] = contact.h3.string.split(' ')[:2]
    lst = contact.find_all("dd")
    ret["entreprise"] = lst[7].string
    ret["email"] = lst[8].text.split(" ")[0]
    ret["phone"] = lst[3].string
    return ret
if __name__ == '__main__':
    conn = sqlite3.connect("./data/database.db")
    for i in range(100):
        ret = generate_contact()
        print(i, ret)
        curr = conn.cursor()
        curr.execute("INSERT INTO contacts VALUES ({},\"{}\",\"{}\",\"{}\",\"{}\",\"{}\",\"{}\")".format(i, ret["email"], ret["firstname"], ret["lastname"], ret["entreprise"],ret["phone"],"picture.png"))
    conn.commit()
    conn.close()
