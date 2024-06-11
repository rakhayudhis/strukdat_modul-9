#include <iostream>
#include <string>
#include <queue>
using namespace std;

struct Pohon {
    char data;
    Pohon *kiri, *kanan, *inti;
};

Pohon *root;

void init() {
    root = NULL;
}

bool isEmpty() {
    return root == NULL;
}

Pohon *newPohon(char data) {
    Pohon *node = new Pohon();
    node->data = data;
    node->kiri = NULL;
    node->kanan = NULL;
    node->inti = NULL;
    return node;
}

void buatNode(char data) {
    if (isEmpty()) {
        root = newPohon(data);
        cout << "\nNode " << data << " berhasil dibuat menjadi root." << endl;
    } else {
        cout << "\nPohon sudah dibuat" << endl;
    }
}

Pohon *insertkiri(char data, Pohon *node) {
    if (isEmpty()) {
        cout << "\nBuat tree terlebih dahulu!" << endl;
        return NULL;
    } else {
        if (node->kiri != NULL) {
            cout << "\nNode " << node->data << " sudah ada child kiri!" << endl;
            return NULL;
        } else {
            Pohon *baru = newPohon(data);
            baru->inti = node;
            node->kiri = baru;
            cout << "\nNode " << data << " berhasil ditambahkan ke child kiri " << node->data << endl;
            return baru;
        }
    }
}

Pohon *insertkanan(char data, Pohon *node) {
    if (isEmpty()) {
        cout << "\nBuat tree terlebih dahulu!" << endl;
        return NULL;
    } else {
        if (node->kanan != NULL) {
            cout << "\nNode " << node->data << " sudah ada child kanan!" << endl;
            return NULL;
        } else {
            Pohon *baru = newPohon(data);
            baru->inti = node;
            node->kanan = baru;
            cout << "\nNode " << data << " berhasil ditambahkan ke child kanan " << node->data << endl;
            return baru;
        }
    }
}

void preOrder(Pohon *node) {
    if (node != NULL) {
        cout << " " << node->data << ", ";
        preOrder(node->kiri);
        preOrder(node->kanan);
    }
}

void inOrder(Pohon *node) {
    if (node != NULL) {
        inOrder(node->kiri);
        cout << " " << node->data << ", ";
        inOrder(node->kanan);
    }
}

void postOrder(Pohon *node) {
    if (node != NULL) {
        postOrder(node->kiri);
        postOrder(node->kanan);
        cout << " " << node->data << ", ";
    }
}

void displayChild(Pohon *node) {
    if (node != NULL) {
        cout << "inti: " << node->data << endl;
        if (node->kiri != NULL) {
            cout << "Child Kiri: " << node->kiri->data << endl;
        } else {
            cout << "Child Kiri: (tidak punya child kiri)" << endl;
        }
        if (node->kanan != NULL) {
            cout << "Child Kanan: " << node->kanan->data << endl;
        } else {
            cout << "Child Kanan: (tidak punya child kanan)" << endl;
        }
    }
}

void displayDescendants(Pohon *node) {
    if (node != NULL) {
        cout << "Descendants of " << node->data << ": ";
        queue<Pohon *> q;
        if (node->kiri != NULL) q.push(node->kiri);
        if (node->kanan != NULL) q.push(node->kanan);
        while (!q.empty()) {
            Pohon *temp = q.front();
            q.pop();
            cout << temp->data << " ";
            if (temp->kiri != NULL) q.push(temp->kiri);
            if (temp->kanan != NULL) q.push(temp->kanan);
        }
        cout << endl;
    }
}

Pohon *findNode(Pohon *node, char data) {
    if (node == NULL) return NULL;
    if (node->data == data) return node;
    Pohon *kiriResult = findNode(node->kiri, data);
    if (kiriResult != NULL) return kiriResult;
    return findNode(node->kanan, data);
}

int main() {
    int choice;
    char data;
    init();

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Buat Node Root\n";
        cout << "2. Tambah Node Kiri\n";
        cout << "3. Tambah Node Kanan\n";
        cout << "4. Tampilkan PreOrder\n";
        cout << "5. Tampilkan InOrder\n";
        cout << "6. Tampilkan PostOrder\n";
        cout << "7. Tampilkan Child Node\n";
        cout << "8. Tampilkan Descendants Node\n";
        cout << "9. Keluar\n";
        cout << "Pilih opsi: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                cout << "Masukkan data untuk root: ";
                cin >> data;
                buatNode(data);
                break;
            case 2: {
                cout << "Masukkan data untuk node kiri: ";
                cin >> data;
                cout << "Masukkan data inti: ";
                char intiData;
                cin >> intiData;
                Pohon *inti = findNode(root, intiData);
                if (inti != NULL) {
                    insertkiri(data, inti);
                } else {
                    cout << "\ninti tidak ditemukan!" << endl;
                }
                break;
            }
            case 3: {
                cout << "Masukkan data untuk node kanan: ";
                cin >> data;
                cout << "Masukkan data inti: ";
                char intiData;
                cin >> intiData;
                Pohon *inti = findNode(root, intiData);
                if (inti != NULL) {
                    insertkanan(data, inti);
                } else {
                    cout << "\ninti tidak ditemukan!" << endl;
                }
                break;
            }
            case 4:
                cout << "\nPreOrder: ";
                preOrder(root);
                cout << "\n";
                break;
            case 5:
                cout << "\nInOrder: ";
                inOrder(root);
                cout << "\n";
                break;
            case 6:
                cout << "\nPostOrder: ";
                postOrder(root);
                cout << "\n";
                break;
            case 7:
                cout << "Masukkan data node untuk menampilkan child: ";
                cin >> data;
                {
                    Pohon *node = findNode(root, data);
                    if (node != NULL) {
                        displayChild(node);
                    } else {
                        cout << "\nNode tidak ditemukan!" << endl;
                    }
                }
                break;
            case 8:
                cout << "Masukkan data node untuk menampilkan descendants: ";
                cin >> data;
                {
                    Pohon *node = findNode(root, data);
                    if (node != NULL) {
                        displayDescendants(node);
                    } else {
                        cout << "\nNode tidak ditemukan!" << endl;
                    }
                }
                break;
            case 9:
                return 0;
            default:
                cout << "Opsi tidak valid! Coba lagi." << endl;
        }
    }

    return 0;
}