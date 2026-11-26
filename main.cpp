#include "Grafo.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    try
    {
        int num_vertices;
        int num_arestas;

        cin >> num_vertices >> num_arestas;
        Grafo g(num_vertices);

        for (int i = 0; i < num_arestas; i++)
        {
            int v1, v2;
            cin >> v1 >> v2;
            g.inserir_aresta(Aresta(v1, v2));
        }

        int qtd_remocoes;
        cin >> qtd_remocoes;

        vector<int> influenciadores = g.influenciadores_a_contratar();
        cout << influenciadores.size() << ":";
        for (int i = 0; i < influenciadores.size(); i++)
        {
            cout << " " << influenciadores[i];
        }

        cout << endl;

        for (int i = 0; i < qtd_remocoes; i++)
        {
            int v1, v2;
            cin >> v1 >> v2;

            g.remover_aresta(Aresta(v1, v2));
            influenciadores = g.influenciadores_a_contratar();
            cout << influenciadores.size() << ":";

            for (int j = 0; j < influenciadores.size(); j++)
            {
                cout << " " << influenciadores[j];
            }

            cout << endl;
        }
    }
    catch (const exception &e)
    {
        cerr << "exception: " << e.what() << "\n";
    }

    return 0;
}