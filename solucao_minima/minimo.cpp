#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

// Verifica se os vertices escolhidos dominam o grafo inteiro.
bool domina_todos(const vector<vector<int>>& adj,
                  const vector<int>& escolhidos) {
    const int n = static_cast<int>(adj.size());
    vector<bool> coberto(n, false);

    for (int v : escolhidos) {
        coberto[v] = true; // O proprio influenciador esta coberto.
        for (int u = 0; u < n; ++u) {
            if (adj[v][u] != 0) {
                coberto[u] = true;
            }
        }
    }
    return all_of(coberto.begin(), coberto.end(), [](bool x) { return x; });
}

// Tenta todas as combinacoes de 'quantidade' vertices em ordem crescente.
// A primeira combinacao valida encontrada e devolvida em 'resposta'.
bool buscar_combinacao(const vector<vector<int>>& adj, int inicio,
                      int quantidade, vector<int>& atual,
                      vector<int>& resposta) {
    if (quantidade == 0) {
        if (domina_todos(adj, atual)) {
            resposta = atual;
            return true;
        }
        return false;
    }

    const int n = static_cast<int>(adj.size());
    for (int v = inicio; v <= n - quantidade; ++v) {
        atual.push_back(v);
        if (buscar_combinacao(adj, v + 1, quantidade - 1, atual, resposta)) {
            return true;
        }
        atual.pop_back();
    }
    return false;
}

vector<int> conjunto_dominante_minimo(const vector<vector<int>>& adj) {
    const int n = static_cast<int>(adj.size());
    vector<int> atual, resposta;

    for (int tamanho = 1; tamanho <= n; ++tamanho) {
        if (buscar_combinacao(adj, 0, tamanho, atual, resposta)) {
            return resposta;
        }
    }
    return resposta;
}

int main() {
    int P, C;
    if (!(cin >> P >> C)) return 0;
    if (P <= 0 || C < 0) return 1;

    vector<vector<int>> adj(P, vector<int>(P, 0));
    for (int i = 0; i < C; ++i) {
        int x, y;
        if (!(cin >> x >> y)) return 1;
        if (x < 0 || x >= P || y < 0 || y >= P) return 1;
        if (x != y) {
            adj[x][y] = 1;
            adj[y][x] = 1;
        }
    }

    // O arquivo .in pode conter remocoes depois das conexoes.
    // Elas NAO sao aplicadas: o enunciado pede o grafo original.
    const vector<int> minimo = conjunto_dominante_minimo(adj);
    cout << minimo.size() << ':';
    for (int v : minimo) cout << ' ' << v;
    cout << '\n';
    return 0;
}
