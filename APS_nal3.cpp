#include <iostream>
#include <list>
#include <chrono>

using namespace std;

struct element {
    int key;
    element *prev,
            *next;
};

element *najdi(element *head, int key) {
    element *current = head;
    while (current != nullptr && current->key != key) {
        current = current->next;
    }
    return current;
}

void vstavi_v_glavo(element *&head, element *new_el, element *&tail) {
    new_el->next = head;
    new_el->prev = nullptr;
    if (head != nullptr) {
        head->prev = new_el;
        head = new_el;
    } else {
        head = new_el;
        tail = new_el;
    }
}

void vstavi_za_repom(element *&head, element *new_el, element *&tail) {
    new_el->next = nullptr;
    new_el->prev = tail;
    if (tail != nullptr) {
        tail->next = new_el;
        tail = new_el;
    } else {
        head = new_el;
        tail = new_el;
    }
}

void vstavi_za_elementom(element *current, element *new_el, element *&tail) {
    new_el->prev = current;
    new_el->next = current->next;
    if (current->next != nullptr) {
        current->next->prev = new_el;
    } else {
        tail = new_el;
    }
    current->next = new_el;
}

void brisi(element *&head, element *del_el, element *&tail) {
    if (del_el->prev == nullptr && del_el->next == nullptr) {
        head = nullptr;
        tail = nullptr;
    } else if (del_el->prev != nullptr && del_el->next != nullptr) {
        del_el->prev->next = del_el->next;
        del_el->next->prev = del_el->prev;
    } else if (del_el->prev == nullptr) {
        head = del_el->next;
        head->prev = nullptr;
    } else if (del_el->next == nullptr) {
        tail = del_el->prev;
        tail->next = nullptr;
    }
    delete del_el;
}

void izpisiGlavaDoRep(element *head) {
    element *current = head;
    while (current != nullptr) {
        cout << current->key << " ";
        current = current->next;
    }
    cout << endl;
}

void izpisiRepDoGlava(element *tail) {
    element *current = tail;
    while (current != nullptr) {
        cout << current->key << " ";
        current = current->prev;
    }
    cout << endl;
}

int main() {

    element *glava = nullptr;
    element *rep = nullptr;

    while (true) {
        cout << endl;
        cout << "1. Iskanje podatka" << endl;
        cout << "2. Vnos podatka v glavo" << endl;
        cout << "3. Vnos podatka za elementom" << endl;
        cout << "4. Vnos podatka za repom" << endl;
        cout << "5. Brisanje podatka" << endl;
        cout << "6. Izpis seznama od glave proti repu" << endl;
        cout << "7. Izpis seznama od repa proti glavi" << endl;
        cout << "8. Testiraj hitrost" << endl;
        cout << "9. Konec" << endl;

        int izbira;
        cout << "vnesite steviko menija: " << endl;
        cin >> izbira;

        if (izbira == 1) {
            int iskanaVrednost;
            cout << "Vnesite vrednost, ki jo zelite poiskati: ";
            cin >> iskanaVrednost;

            element *rezultat = najdi(glava, iskanaVrednost);

            if (rezultat != nullptr) {
                cout << "Iskana vrednost: (" << iskanaVrednost << ") ZE OBSTAJA" << endl;
            } else {
                cout << "Iskana vrednost: (" << iskanaVrednost << ") SE NE OBSTAJA" << endl;
            }

            najdi(glava, iskanaVrednost);

        } else if (izbira == 2) {
            int novElementKey;
            cout << "Kateri element zelite vstavit v glavo?" << endl;
            cin >> novElementKey;

            element *novElement = new element();
            novElement->key = novElementKey;

            vstavi_v_glavo(glava, novElement, rep);

        } else if (izbira == 3) {
            int novElementKey;
            cout << "Kateri element zelite vstavit?" << endl;
            cin >> novElementKey;

            element *novElement = new element();
            novElement->key = novElementKey;

            int trenutni;
            cout << "Za katerim elementom ga zelite vstaviti?" << endl;
            cin >> trenutni;

            element *trenutniElement = new element();
            trenutniElement->key = trenutni;

            element *rezultat = najdi(glava, trenutni);
            if (rezultat != nullptr) {
                vstavi_za_elementom(rezultat, novElement, rep);
            } else {
                cout << "Element za katerim hocete vstavit vrednost, NE OBSTAJA" << endl;
            }

        } else if (izbira == 4) {
            int novElementKey;
            cout << "Kateri element zelite vstavit za repom?" << endl;
            cin >> novElementKey;

            element *novElement = new element();
            novElement->key = novElementKey;

            vstavi_za_repom(glava, novElement, rep);

        } else if (izbira == 5) {
            int brisiElementKey;
            cout << "Kateri element zelite zbristi?" << endl;
            cin >> brisiElementKey;

            element *rezultat = najdi(glava, brisiElementKey);
            if (rezultat != nullptr) {
                brisi(glava, rezultat, rep);
            } else {
                cout << "Element, ki ga zelite zbrisati, NE OBSTAJA" << endl;
            }
        } else if (izbira == 6) {
            izpisiGlavaDoRep(glava);
        } else if (izbira == 7) {
            izpisiRepDoGlava(rep);
        } else if (izbira == 8) {
            int st_elementov;
            cout << "Za koliko elementov zelite testirati hitrost seznama?" << endl;
            cin >> st_elementov;

            list<long long> seznam;

            auto start_time = std::chrono::steady_clock::now();
            for (long long i = 0; i < st_elementov; ++i) {
                long long nov_element = i + 1;
                seznam.push_front(nov_element);
            }
            auto end_time = std::chrono::steady_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
            cout << "Cas vstavljanja " << st_elementov << " elementov v glavo seznama: " << duration.count()
                 << " mikrosekund." << endl;

            auto start_time1 = std::chrono::steady_clock::now();
            long long vsota_seznam = 0;
            for (long long elm: seznam) {
                vsota_seznam += elm;
            }

            auto end_time1 = std::chrono::steady_clock::now();
            auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(end_time1 - start_time1);
            cout << "Cas potreben za vsoto vseh kljucev v seznamu: " << duration1.count() << " mikrosekund." << endl;

            long long polje[st_elementov];

            auto start_time2 = std::chrono::steady_clock::now();
            for (long long i = 1; i <= st_elementov; ++i) {
                for (long long j = i - 1; j > 0; --j) {
                    polje[j] = polje[j - 1];
                }
                polje[0] = i;
            }
            auto end_time2 = std::chrono::steady_clock::now();
            auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(end_time2 - start_time2);
            cout << "Cas potreben za vstavljanje na prvo mesto v polju: " << duration2.count() << " mikrosekund."
                 << endl;

            auto start_time3 = std::chrono::steady_clock::now();
            long long vsota_polje = 0;
            for (long long i = 0; i < st_elementov; ++i) {
                vsota_polje += polje[i];
            }
            auto end_time3 = std::chrono::steady_clock::now();
            auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(end_time3 - start_time3);
            cout << "Cas potreben za racunanje vsote vrednosti v polju: " << duration3.count() << " mikrosekund."
                 << endl;

            long long polje2[st_elementov];

            auto start_time4 = std::chrono::steady_clock::now();
            for (long long i = 0; i < st_elementov; ++i) {
                polje2[i] = i;
            }
            auto end_time4 = std::chrono::steady_clock::now();
            auto duration4 = std::chrono::duration_cast<std::chrono::microseconds>(end_time4 - start_time4);
            cout << "Cas potreben za vstavljanje na zadnje mesto v polju: " << duration4.count() << " mikrosekund."
                 << endl;

            cout << "Vsota seznama: " << vsota_seznam << endl;
            cout << "Vsota polja: " << vsota_polje << endl;

        } else if (izbira == 9) {
            break;
        }
    }
    return 0;
}
