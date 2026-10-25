#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <list>
#include <fstream>

using namespace std;
using namespace std::chrono;

void print(int elem) {
    cout << elem << " ";
}

int main(){
// create list with elements from 1 to 9
//vector<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};
// find position of element with value 5
//vector<int>:: const_iterator pos;
//pos = find(coll.cbegin(), coll.cend(),3) ;
// print value to which iterator pos refers
//cout<< "pos: " << *pos << endl;
// convert iterator to reverse iterator rpos
//vector<int>:: const_reverse_iterator rpos(pos);
// print value to which reverse iterator rpos refers
//cout << "rpos: "<< *rpos << endl;

    ///iterator
    /*vector<int> coll = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    vector<int>:: const_iterator pos1;
    pos1 = find(coll.cbegin(), coll.cend(), 2);
    vector<int>:: const_iterator pos2;
    pos2 = find(coll.cbegin(), coll.cend(), 7);

    cout << "Lecture normale  : ";
    for_each(pos1, pos2, print);
    cout << endl;

    vector<int>::const_reverse_iterator rpos1(pos1);
    vector<int>::const_reverse_iterator rpos2(pos2);

    cout << "Lecture inversee : ";
    for_each(rpos2, rpos1, print);
    cout << endl;*/


    ///iteratot et insertion
    /*vector<int> v={1,2,3};
    auto it=v.begin();
    v.insert(v.begin(),0);
    //la solution est de creer un nouveau iterator pour ne pas avoir des erreur (a chaque fois un valeur qlq)
    auto nvIt=v.begin();
    cout << *nvIt;*/



    ///quel conteneur est plus rapide vector ou liste
    cout << "=== CHARGEMENT DU FICHIER DE DONNEES ===" << endl;

    ifstream monFichier("roman.txt");
    if (!monFichier) {
        cout << "Erreur : Impossible d'ouvrir le fichier !" << endl;
        return 1;
    }

    vector<string> v_orig;
    list<string> l_orig;
    string mot;

    auto start_load = high_resolution_clock::now();
    while (monFichier >> mot) {
        v_orig.push_back(mot);
        l_orig.push_back(mot);
    }
    monFichier.close();
    auto end_load = high_resolution_clock::now();

    cout << "Fichier charge : " << v_orig.size() << " elements en "
         << duration_cast<milliseconds>(end_load - start_load).count() << " ms.\n" << endl;


    {
        cout << "=== TEST 1 : INSERTIONS (Fin, Debut, Milieu) ===" << endl;
        const int N_INSER = 2000;

        // 1.1 Insertion à la FIN
        auto start = high_resolution_clock::now();
        vector<string> v_f;
        for(int i = 0; i < N_INSER; i++) v_f.push_back(v_orig[i]);
        auto end = high_resolution_clock::now();
        cout << "Vector (Insertion a la FIN) : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

        start = high_resolution_clock::now();
        list<string> l_f;
        for(int i = 0; i < N_INSER; i++) l_f.push_back(v_orig[i]);
        end = high_resolution_clock::now();
        cout << "List   (Insertion a la FIN) : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

        // 1.2 Insertion au DÉBUT (insert vs push_front)
        start = high_resolution_clock::now();
        vector<string> v_d;
        for(int i = 0; i < N_INSER; i++) v_d.insert(v_d.begin(), v_orig[i]);
        end = high_resolution_clock::now();
        cout << "Vector (Insertion au DEBUT)  : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

        start = high_resolution_clock::now();
        list<string> l_d;
        for(int i = 0; i < N_INSER; i++) l_d.push_front(v_orig[i]);
        end = high_resolution_clock::now();
        cout << "List   (Insertion au DEBUT)    : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

        // 1.3 Insertion au MILIEU
        start = high_resolution_clock::now();
        vector<string> v_m_ins;
        for(int i = 0; i < N_INSER; i++) {
            v_m_ins.insert(v_m_ins.begin() + v_m_ins.size() / 2, v_orig[i]);
        }
        end = high_resolution_clock::now();
        cout << "Vector (Insertion au MILIEU)    : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

        start = high_resolution_clock::now();
        list<string> l_m_ins;
        for(int i = 0; i < N_INSER; i++) {
            auto it = l_m_ins.begin();
            advance(it, l_m_ins.size() / 2);
            l_m_ins.insert(it, v_orig[i]);
        }
        end = high_resolution_clock::now();
        cout << "List   (Insertion au MILIEU)    : " << duration_cast<microseconds>(end - start).count() << " us\n" << endl;
    }



    {
        cout << "=== TEST 2 : SUPPRESSIONS (Debut, Milieu, Fin) ===" << endl;
        const int N_SUPPR = 1000;

        // 2.1 Suppression au DÉBUT
        vector<string> v_s(v_orig.begin(), v_orig.begin() + N_SUPPR);
        list<string> l_s(v_orig.begin(), v_orig.begin() + N_SUPPR);

        auto start = high_resolution_clock::now();
        for(int i = 0; i < N_SUPPR; i++) v_s.erase(v_s.begin());
        auto end = high_resolution_clock::now();
        cout << "Vector (Suppression au DEBUT)   : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

        start = high_resolution_clock::now();
        for(int i = 0; i < N_SUPPR; i++) l_s.pop_front();
        end = high_resolution_clock::now();
        cout << "List   (Suppression au DEBUT)     : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

        // 2.2 Suppression au MILIEU
        vector<string> v_m(v_orig.begin(), v_orig.begin() + N_SUPPR);
        list<string> l_m(v_orig.begin(), v_orig.begin() + N_SUPPR);

        start = high_resolution_clock::now();
        v_m.erase(v_m.begin() + v_m.size() / 2);
        end = high_resolution_clock::now();
        cout << "Vector (Suppression au MILIEU)     : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

        start = high_resolution_clock::now();
        auto it = l_m.begin();
        advance(it, l_m.size() / 2);
        l_m.erase(it);
        end = high_resolution_clock::now();
        cout << "List   (Suppression au MILIEU) : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

        // 2.3 Suppression à la FIN
        vector<string> v_f_sup(v_orig.begin(), v_orig.begin() + 5000);
        list<string> l_f_sup(v_orig.begin(), v_orig.begin() + 5000);

        start = high_resolution_clock::now();
        for(int i = 0; i < 5000; i++) v_f_sup.pop_back();
        end = high_resolution_clock::now();
        cout << "Vector (Suppression a la FIN)  : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

        start = high_resolution_clock::now();
        for(int i = 0; i < 5000; i++) l_f_sup.pop_back();
        end = high_resolution_clock::now();
        cout << "List   (Suppression a la FIN)  : " << duration_cast<microseconds>(end - start).count() << " us\n" << endl;
    }



    {
        cout << "=== TEST 3 : RECHERCHE (std::find) ===" << endl;
        string cible = v_orig.back();

        auto start = high_resolution_clock::now();
        auto p_v = find(v_orig.begin(), v_orig.end(), cible);
        auto end = high_resolution_clock::now();
        bool trouve_v = (p_v != v_orig.end());
        cout << "Vector (RECHERCHE) : " << duration_cast<microseconds>(end - start).count() << " us (Trouve: " << trouve_v << ")" << endl;

        start = high_resolution_clock::now();
        auto p_l = find(l_orig.begin(), l_orig.end(), cible);
        end = high_resolution_clock::now();
        bool trouve_l = (p_l != l_orig.end());
        cout << "List   (RECHERCHE) : " << duration_cast<microseconds>(end - start).count() << " us (Trouve: " << trouve_l << ")\n" << endl;
    }



    {
        cout << "=== TEST 4 : MODIFICATION ===" << endl;
        vector<string> v_mod = v_orig;
        list<string> l_mod = l_orig;
        const int REPETITIONS = 1000;

        // Vector : Accès direct avec []
        auto start = high_resolution_clock::now();
        for(int i = 0; i < REPETITIONS; i++) {
            v_mod[i] = "MODIF";
        }
        auto end = high_resolution_clock::now();
        cout << "Vector (modification []) : " << duration_cast<microseconds>(end - start).count() << " us" << endl;

        // List : Marche à pied avec advance
        start = high_resolution_clock::now();
        for(int i = 0; i < REPETITIONS; i++) {
            auto it = l_mod.begin();
            advance(it, i);
            *it = "MODIF";
        }
        end = high_resolution_clock::now();
        cout << "List   (modification)    : " << duration_cast<microseconds>(end - start).count() << " us" << endl;
    }

    return 0;
}
