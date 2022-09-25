#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

struct monstro {
    int id;
    int tipo;
    int level;
    string nome;
    int hp;
    int hpmax;
    int mana;
    int manamax;
    int atk;
    int def;
    int forca;
    int agil;
    int intel;
    int resis;
    int xp;
    int gold;
};

struct personagem {
    string nome;
    int hp;
    int hpmax;
    int mana;
    int manamax;
    int atk;
    int def;
    int forca;
    int agil;
    int intel;
    int resis;
    int xp;
    int level;
    int gold;
    int pontos;
};

struct habilidades { // id = 0
    int id;
    string nome;
    int golpes;
    float multiplicador;
    int custo;
    float redDef;
    float redDano;
    float cura;
    int cd;
    int cdAtual;
    int buff;
};

struct armas { // id = ar001
    int id;
    int danoMin;
    int danoMax;
    int forca;
    int agil;
    int intel;
    int resis;
    int raridade;
};

struct equipamentos {

};

void status (personagem &player) {
    player.hpmax = (5*player.level)+(10*player.resis)+(2*player.forca);
    player.manamax = (5*player.level)+(10*player.intel);
    player.atk = (2*player.level)+(3*player.forca)+(1*player.agil);
    player.def = (1*player.level)+(1*player.resis);
}

void nivel (personagem &player) {
    if (player.xp >= 100 and player.level == 1) {
        player.xp -= 100;
        player.level = 2;
        player.pontos += 2;
    } else if (player.xp >= 200 and player.level == 2) {
        player.xp -= 200;
        player.level = 3;
        player.pontos += 4;
    } else if (player.xp >= 400 and player.level == 3) {
        player.xp -= 400;
        player.level = 4;
        player.pontos += 6;
    } else if (player.xp >= 800 and player.level == 4) {
        player.xp -= 800;
        player.level = 5;
        player.pontos += 8;
    } else if (player.xp >= 1600 and player.level == 5) {
        player.xp -= 1600;
        player.level = 6;
        player.pontos += 10;
    } else if (player.xp >= 3200 and player.level == 6) {
        player.xp -= 3200;
        player.level = 7;
        player.pontos += 12;
    } else if (player.xp >= 6400 and player.level == 7) {
        player.xp -= 6400;
        player.level = 8;
        player.pontos += 14;
    } else if (player.xp >= 12800 and player.level == 8) {
        player.xp -= 12800;
        player.level = 9;
        player.pontos += 16;
    } else if (player.xp >= 25600 and player.level == 9) {
        player.xp -= 25600;
        player.level = 10;
        player.pontos += 18;
    } else {
        cout << "você ainda não tem a XP necessária para passar de nível!" << endl;
    }
}

int menuPersonagem (int &numero, personagem &player) {
    int aumentos;
    switch (numero) {
        case 1: 
            cout << "Essas são as suas estatísticas: " << endl;
            cout << "LEVEL: " << player.level << endl;
            cout << "HP: " << player.hp << "/" << player.hpmax << endl;
            cout << "MANA: " << player.mana << "/" << player.manamax << endl;
            cout << "ATK: " << player.atk << endl;
            cout << "DEF: " << player.def << endl;
            cout << "FORÇA: " << player.forca << endl;
            cout << "AGILIDADE: " << player.agil << endl;
            cout << "INTELIGÊNCIA: " << player.intel << endl;
            cout << "RESISTÊNCIA: " << player.resis << endl;
            cout << "PONTOS LIVRES: " << player.pontos << endl;
            cout << "XP: " << player.xp << endl;
            cout << "GOLD: " << player.gold << endl;
            return 0;
            break;
        case 2:
            cout << "Você tem " << player.xp << "de XP. Deseja subir de nível?" << endl;
            cout << "1- Sim!" << endl;
            cout << "2- Não" << endl;
            cin >> numero;
            if (numero == 1) {
                nivel (player);
                status (player);
            } else {
                return 0;
            }
            break;
        case 3:
            if (player.pontos > 0) {
                cout << "Você tem " << player.pontos << "Pontos Livres. Deseja Gastá-los?" << endl;
                cout << "1- Sim!" << endl;
                cout << "2- Não" << endl;
                cin >> numero;
            
                if (numero == 1) {
                    while (numero < 5) {
                        cout << "Escolha uma estatística para alocar seus Pontos: " << endl;
                        cout << "1- Força" << endl;
                        cout << "2- Agilidade" << endl;
                        cout << "3- Inteligência" << endl;
                        cout << "4- Resistência" << endl;
                        cout << "5- Mudei de Ideia" << endl;
                        cin >> numero;
                        if (numero == 1) { // força
                            if (player.forca < 15) {
                                cout << "Você escolheu Força. Você precisará gastar 1 Ponto Livre para cada aumento nessa estatística." << endl;
                                cout << "Você possui " << player.pontos << "Pontos Livres. Quantos aumentos você deseja realizar?";
                                cin >> aumentos;
                                if (aumentos <= player.pontos and player.forca+aumentos <= 15) {
                                    cout << "Deseja realizar " << aumentos << "aumentos utilizando " << aumentos << "Pontos Livres?" << endl;
                                    cout << "1- Sim!" << endl;
                                    cout << "2- Mudei de Ideia, vou virar mago!" << endl;
                                    cin >> numero;
                                    if (numero == 1) {
                                        player.forca += aumentos;
                                        player.pontos -= aumentos;
                                        cout << "Sua Força aumentou em " << aumentos << "com sucesso!" << endl;
                                        status(player);
                                        numero = 0;
                                    } else {
                                        numero = 0;
                                    }
                                } else {
                                    cout << "O número de aumentos é superior à sua categoria. O máximo de aumentos que você pode realizar agora é: " << 15-player.forca << endl;
                                }
                            } else if (player.forca >= 15 and player.forca < 30) {
                                cout << "Você escolheu Força. Você precisará gastar 2 Pontos Livres para cada aumento nessa estatística." << endl;
                                cout << "Você possui " << player.pontos << "Pontos Livres. Quantos aumentos você deseja realizar?";
                                cin >> aumentos;
                                if (aumentos <= player.pontos/2 and player.forca+aumentos <= 30) {
                                    cout << "Deseja realizar " << aumentos << "aumentos utilizando " << aumentos*2 << "Pontos Livres?" << endl;
                                    cout << "1- Sim!" << endl;
                                    cout << "2- Mudei de Ideia, vou virar mago!" << endl;
                                    cin >> numero;
                                    if (numero == 1) {
                                        player.forca += aumentos;
                                        player.pontos -= 2*aumentos;
                                        cout << "Sua Força aumentou em " << aumentos << "com sucesso!" << endl;
                                        status(player);
                                        numero = 0;
                                    } else {
                                        numero = 0;
                                    }
                                } else {
                                    cout << "O número de aumentos é superior à sua categoria. O máximo de aumentos que você pode realizar agora é: " << 30-player.forca << endl;
                                }
                            } else if (player.forca >= 30 and player.forca < 45) {
                                cout << "Você escolheu Força. Você precisará gastar 3 Pontos Livres para cada aumento nessa estatística." << endl;
                                cout << "Você possui " << player.pontos << "Pontos Livres. Quantos aumentos você deseja realizar?";
                                cin >> aumentos;
                                if (aumentos <= player.pontos/3 and player.forca+aumentos <= 45) {
                                    cout << "Deseja realizar " << aumentos << "aumentos utilizando " << aumentos*3 << "Pontos Livres?" << endl;
                                    cout << "1- Sim!" << endl;
                                    cout << "2- Mudei de Ideia, vou virar mago!" << endl;
                                    cin >> numero;
                                    if (numero == 1) {
                                        player.forca += aumentos;
                                        player.pontos -= 3*aumentos;
                                        cout << "Sua Força aumentou em " << aumentos << "com sucesso!" << endl;
                                        status(player);
                                        numero = 0;
                                    } else {
                                        numero = 0;
                                    }
                                } else {
                                    cout << "O número de aumentos é superior à sua categoria. O máximo de aumentos que você pode realizar agora é: " << 45-player.forca << endl;
                                }
                            }
                        } else if (numero == 2) { // agilidade
                            if (player.agil < 15) {
                                cout << "Você escolheu Agilidade. Você precisará gastar 1 Ponto Livre para cada aumento nessa estatística." << endl;
                                cout << "Você possui " << player.pontos << "Pontos Livres. Quantos aumentos você deseja realizar?";
                                cin >> aumentos;
                                if (aumentos <= player.pontos and player.agil+aumentos <= 15) {
                                    cout << "Deseja realizar " << aumentos << "aumentos utilizando " << aumentos << "Pontos Livres?" << endl;
                                    cout << "1- Sim!" << endl;
                                    cout << "2- Mudei de Ideia, vou virar lutador!" << endl;
                                    cin >> numero;
                                    if (numero == 1) {
                                        player.agil += aumentos;
                                        player.pontos -= aumentos;
                                        cout << "Sua Agilidade aumentou em " << aumentos << "com sucesso!" << endl;
                                        status(player);
                                        numero = 0;
                                    } else {
                                        numero = 0;
                                    }
                                } else {
                                    cout << "O número de aumentos é superior à sua categoria. O máximo de aumentos que você pode realizar agora é: " << 15-player.agil << endl;
                                }
                            } else if (player.agil >= 15 and player.agil < 30) {
                                cout << "Você escolheu Agilidade. Você precisará gastar 2 Pontos Livres para cada aumento nessa estatística." << endl;
                                cout << "Você possui " << player.pontos << "Pontos Livres. Quantos aumentos você deseja realizar?";
                                cin >> aumentos;
                                if (aumentos <= player.pontos/2 and player.agil+aumentos <= 30) {
                                    cout << "Deseja realizar " << aumentos << "aumentos utilizando " << aumentos*2 << "Pontos Livres?" << endl;
                                    cout << "1- Sim!" << endl;
                                    cout << "2- Mudei de Ideia, vou virar lutador!" << endl;
                                    cin >> numero;
                                    if (numero == 1) {
                                        player.agil += aumentos;
                                        player.pontos -= 2*aumentos;
                                        cout << "Sua Agilidade aumentou em " << aumentos << "com sucesso!" << endl;
                                        status(player);
                                        numero = 0;
                                    } else {
                                        numero = 0;
                                    }
                                } else {
                                    cout << "O número de aumentos é superior à sua categoria. O máximo de aumentos que você pode realizar agora é: " << 30-player.agil << endl;
                                }
                            } else if (player.agil >= 30 and player.agil < 45) {
                                cout << "Você escolheu Agilidade. Você precisará gastar 3 Pontos Livres para cada aumento nessa estatística." << endl;
                                cout << "Você possui " << player.pontos << "Pontos Livres. Quantos aumentos você deseja realizar?";
                                cin >> aumentos;
                                if (aumentos <= player.pontos/3 and player.agil+aumentos <= 45) {
                                    cout << "Deseja realizar " << aumentos << "aumentos utilizando " << aumentos*3 << "Pontos Livres?" << endl;
                                    cout << "1- Sim!" << endl;
                                    cout << "2- Mudei de Ideia, vou virar lutador!" << endl;
                                    cin >> numero;
                                    if (numero == 1) {
                                        player.agil += aumentos;
                                        player.pontos -= 3*aumentos;
                                        cout << "Sua Agilidade aumentou em " << aumentos << "com sucesso!" << endl;
                                        status(player);
                                        numero = 0;
                                    } else {
                                        numero = 0;
                                    }
                                } else {
                                    cout << "O número de aumentos é superior à sua categoria. O máximo de aumentos que você pode realizar agora é: " << 45-player.agil << endl;
                                }
                            }
                        } else if (numero == 3) {
                            if (player.intel < 15) {
                                cout << "Você escolheu Inteligencia. Você precisará gastar 1 Ponto Livre para cada aumento nessa estatística." << endl;
                                cout << "Você possui " << player.pontos << "Pontos Livres. Quantos aumentos você deseja realizar?";
                                cin >> aumentos;
                                if (aumentos <= player.pontos and player.intel+aumentos <= 15) {
                                    cout << "Deseja realizar " << aumentos << "aumentos utilizando " << aumentos << "Pontos Livres?" << endl;
                                    cout << "1- Sim!" << endl;
                                    cout << "2- Mudei de Ideia, vou virar guerreiro!" << endl;
                                    cin >> numero;
                                    if (numero == 1) {
                                        player.intel += aumentos;
                                        player.pontos -= aumentos;
                                        cout << "Sua Inteligência aumentou em " << aumentos << "com sucesso!" << endl;
                                        status(player);
                                        numero = 0;
                                    } else {
                                        numero = 0;
                                    }
                                } else {
                                    cout << "O número de aumentos é superior à sua categoria. O máximo de aumentos que você pode realizar agora é: " << 15-player.intel << endl;
                                }
                            } else if (player.intel >= 15 and player.intel < 30) {
                                cout << "Você escolheu Inteligência. Você precisará gastar 2 Pontos Livres para cada aumento nessa estatística." << endl;
                                cout << "Você possui " << player.pontos << "Pontos Livres. Quantos aumentos você deseja realizar?";
                                cin >> aumentos;
                                if (aumentos <= player.pontos/2 and player.intel+aumentos <= 30) {
                                    cout << "Deseja realizar " << aumentos << "aumentos utilizando " << aumentos*2 << "Pontos Livres?" << endl;
                                    cout << "1- Sim!" << endl;
                                    cout << "2- Mudei de Ideia, vou virar guerreiro!" << endl;
                                    cin >> numero;
                                    if (numero == 1) {
                                        player.intel += aumentos;
                                        player.pontos -= 2*aumentos;
                                        cout << "Sua Inteligência aumentou em " << aumentos << "com sucesso!" << endl;
                                        status(player);
                                        numero = 0;
                                    } else {
                                        numero = 0;
                                    }
                                } else {
                                    cout << "O número de aumentos é superior à sua categoria. O máximo de aumentos que você pode realizar agora é: " << 30-player.intel << endl;
                                }
                            } else if (player.intel >= 30 and player.intel < 45) {
                                cout << "Você escolheu Inteligência. Você precisará gastar 3 Pontos Livres para cada aumento nessa estatística." << endl;
                                cout << "Você possui " << player.pontos << "Pontos Livres. Quantos aumentos você deseja realizar?";
                                cin >> aumentos;
                                if (aumentos <= player.pontos/3 and player.intel+aumentos <= 45) {
                                    cout << "Deseja realizar " << aumentos << "aumentos utilizando " << aumentos*3 << "Pontos Livres?" << endl;
                                    cout << "1- Sim!" << endl;
                                    cout << "2- Mudei de Ideia, vou virar guerreiro!" << endl;
                                    cin >> numero;
                                    if (numero == 1) {
                                        player.intel += aumentos;
                                        player.pontos -= 3*aumentos;
                                        cout << "Sua Inteligência aumentou em " << aumentos << "com sucesso!" << endl;
                                        status(player);
                                        numero = 0;
                                    } else {
                                        numero = 0;
                                    }
                                } else {
                                    cout << "O número de aumentos é superior à sua categoria. O máximo de aumentos que você pode realizar agora é: " << 45-player.intel << endl;
                                }
                            }
                        } else if (numero == 4) {
                            if (player.resis < 15) {
                                cout << "Você escolheu Resistência. Você precisará gastar 1 Ponto Livre para cada aumento nessa estatística." << endl;
                                cout << "Você possui " << player.pontos << "Pontos Livres. Quantos aumentos você deseja realizar?";
                                cin >> aumentos;
                                if (aumentos <= player.pontos and player.resis+aumentos <= 15) {
                                    cout << "Deseja realizar " << aumentos << "aumentos utilizando " << aumentos << "Pontos Livres?" << endl;
                                    cout << "1- Sim!" << endl;
                                    cout << "2- Mudei de Ideia, vou virar assassino!" << endl;
                                    cin >> numero;
                                    if (numero == 1) {
                                        player.resis += aumentos;
                                        player.pontos -= aumentos;
                                        cout << "Sua Resistência aumentou em " << aumentos << "com sucesso!" << endl;
                                        status(player);
                                        numero = 0;
                                    } else {
                                        numero = 0;
                                    }
                                } else {
                                    cout << "O número de aumentos é superior à sua categoria. O máximo de aumentos que você pode realizar agora é: " << 15-player.resis << endl;
                                }
                            } else if (player.resis >= 15 and player.resis < 30) {
                                cout << "Você escolheu Resistência. Você precisará gastar 2 Pontos Livres para cada aumento nessa estatística." << endl;
                                cout << "Você possui " << player.pontos << "Pontos Livres. Quantos aumentos você deseja realizar?";
                                cin >> aumentos;
                                if (aumentos <= player.pontos/2 and player.resis+aumentos <= 30) {
                                    cout << "Deseja realizar " << aumentos << "aumentos utilizando " << aumentos*2 << "Pontos Livres?" << endl;
                                    cout << "1- Sim!" << endl;
                                    cout << "2- Mudei de Ideia, vou virar assassino!" << endl;
                                    cin >> numero;
                                    if (numero == 1) {
                                        player.resis += aumentos;
                                        player.pontos -= 2*aumentos;
                                        cout << "Sua Resistência aumentou em " << aumentos << "com sucesso!" << endl;
                                        status(player);
                                        numero = 0;
                                    } else {
                                        numero = 0;
                                    }
                                } else {
                                    cout << "O número de aumentos é superior à sua categoria. O máximo de aumentos que você pode realizar agora é: " << 30-player.resis << endl;
                                }
                            } else if (player.resis >= 30 and player.resis < 45) {
                                cout << "Você escolheu Resistência. Você precisará gastar 3 Pontos Livres para cada aumento nessa estatística." << endl;
                                cout << "Você possui " << player.pontos << "Pontos Livres. Quantos aumentos você deseja realizar?";
                                cin >> aumentos;
                                if (aumentos <= player.pontos/3 and player.resis+aumentos <= 45) {
                                    cout << "Deseja realizar " << aumentos << "aumentos utilizando " << aumentos*3 << "Pontos Livres?" << endl;
                                    cout << "1- Sim!" << endl;
                                    cout << "2- Mudei de Ideia, vou virar lutador!" << endl;
                                    cin >> numero;
                                    if (numero == 1) {
                                        player.resis += aumentos;
                                        player.pontos -= 3*aumentos;
                                        cout << "Sua Resistência aumentou em " << aumentos << "com sucesso!" << endl;
                                        status(player);
                                        numero = 0;
                                    } else {
                                        numero = 0;
                                    }
                                } else {
                                    cout << "O número de aumentos é superior à sua categoria. O máximo de aumentos que você pode realizar agora é: " << 45-player.resis << endl;
                                }
                            }
                        }
                    }
                }
            } else {
                cout << "Você não tem Pontos Livres no momento." << endl;
                return 0;
            }
            return 0;
            break;
        case 4:
            return 4;
            break;
    }

    return 0;
}

int visualizarPersonagem (int &numero, personagem &player) {
    numero = 0;

    while (numero < 4) {
        cout << "Bem vindo " << player.nome << "! Digite um número de acordo com as opções: " << endl;
        cout << "1 - Visualizar Estatísticas:" << endl;
        cout << "2 - Subir de Nível" << endl;
        cout << "3 - Distribuir Pontos" << endl;
        cout << "4 - Voltar ao Menu Principal" << endl;
        cin >> numero;
        menuPersonagem (numero, player);
    }

    return 0;
}

void statusMonstros (monstro mobs[]) { // atualizar conforme aumentar os monstros
    for (int i = 0; i < 140; i++) {
        mobs[i].hp = 1*(mobs[i].tipo)*(mobs[i].level)+(4*(mobs[i].tipo)*(mobs[i].resis))+1*(mobs[i].forca);
        mobs[i].hpmax = mobs[i].hp;
        mobs[i].mana = (1*mobs[i].tipo)*(mobs[i].level)+(3*mobs[i].tipo)*(mobs[i].intel);
        mobs[i].manamax = mobs[i].mana;
        mobs[i].atk = (1*mobs[i].tipo)*(mobs[i].level)+(2*mobs[i].forca)+(1*mobs[i].agil);
        mobs[i].def = (1*mobs[i].tipo)*(mobs[i].level)+(1*mobs[i].resis);
    }
}

void recarregarMonstro (monstro mobs[], int vet[], int r) { // atualizar conforme aumentar os monstros
    mobs[vet[r]].hp = mobs[vet[r]].hpmax;
    mobs[vet[r]].mana = mobs[vet[r]].manamax;
}

void exportar (personagem player) {
    ofstream saida ("personagem.txt");
    saida << player.nome << endl << player.hp << endl << player.hpmax << endl << player.mana << endl << player.manamax << endl << player.atk << endl << player.def << endl << player.forca << endl << player.agil << endl << player.intel << endl << player.resis << endl << player.xp << endl << player.level << endl << player.gold << endl << player.pontos << endl;
    saida.close();
    cout << "Salvo com sucesso!" << endl;
}

void curar (personagem &player) {
    int numero = 0;

    if (player.hp < player.hpmax or player.mana < player.manamax) {
        cout << "Deseja recuperar o seu HP e MANA gastando 1 gold?" << endl;
        cout << "1- Sim!" << endl;
        cout << "2- Não, eu sou masoquista, gosto de ficar ferido." << endl;
        cin >> numero;
        if (numero == 1) {
            player.hp = player.hpmax;
            player.mana = player.manamax;
            player.gold -= 1;
            cout << "Curado com sucesso!" << endl;
        } else {
            cout << "Se morrer a culpa não é minha" << endl;
        }
    }
}

int danoCausado (monstro mobs[], personagem &player, int vet[], int r, habilidades spells[], int n) {
    int dano = (spells[n-1].golpes)*((player.atk*spells[n-1].multiplicador)-(mobs[vet[r]].def*spells[n-1].redDef));

    if (player.hp + (dano*spells[n-1].cura) >= player.hpmax) {
        player.hp = player.hpmax;
    } else {
        player.hp += (dano*spells[n-1].cura) >= player.hpmax;
    }

    if (spells[n-1].id == 5) {
       for (int i = 0; i < 10 ; i++) {
            spells[i].redDef -= 0.5;
            spells[i].buff = 2;
        } 
    }

    for (int i = 0; i < 10; i++) {
        if (spells[i].cdAtual > 0) {
            spells[i].cdAtual--;
        }
    }

    for (int i = 0; i < 10; i++) {
        if (spells[i].buff > 0) {
            spells[i].buff--;

            if (spells[i].buff == 0) {
                spells[i].redDef += 0.5;
            }
        }
    }

    spells[n-1].cdAtual = spells[n-1].cd;

    return dano;
}

int danoSofrido (monstro mobs[], personagem &player, int vet[], int r, habilidades spells[], int n) {
    int dano = (mobs[vet[r]].atk - player.def)*spells[n-1].redDano;
    
    return dano;
}

void recarregarSpell (habilidades spells[]) {
    for (int i = 0; i < 10; i++) {
            spells[i].cdAtual = 0;
    }

    for (int i = 0; i < 10; i++) {
        while (spells[i].buff > 0) {
            spells[i].buff--;

            if (spells[i].buff == 0) {
                spells[i].redDef += 0.5;
            }
        }
    }
}

void batalha (monstro mobs[], personagem &player, int vet[], int r, habilidades spells[]) {
    int n;
    int dano;
    int gold;
    unsigned seed = time(0);
    srand(seed);

    cout << mobs[vet[r]].nome << endl;
    cout << "HP: " << mobs[vet[r]].hp << "/" << mobs[vet[r]].hpmax << endl;
    cout << "Mana: " << mobs[vet[r]].mana << "/" << mobs[vet[r]].manamax << endl;
    cout << "ATK: " << mobs[vet[r]].atk << endl;
    cout << "DEF: " << mobs[vet[r]].def << endl;
    cout << "Deseja lutar ou fugir?" << endl << "1- Lutar" << endl << "2- Fugir" << endl;
    cin >> n;
    if (n == 1) {
        while (player.hp > 0 and mobs[vet[r]].hp > 0) {
            if (player.agil > mobs[vet[r]].agil) {
                cout << "Escolha uma opção:" << endl;
                cout << "1- Atacar" << endl;
                cout << "2- Usar Item" << endl;
                cin >> n;

                if (n == 1) {
                    cout << "Escolha uma Habilidade:" << endl;
                    n = 0;

                    while (n < player.level) {
                        if (n == spells[n].id) {
                            cout << n+1 << "- " << spells[n].nome << endl;
                            n++;
                        }
                    }

                    cin >> n;

                    while (n > player.level or n <= 0) {
                        cout << "Você inseriu um valor inválido. Insira novamente." << endl;
                        cin >> n;
                    }

                    cout << "Você utilizou a habilidade " << spells[n-1].nome << endl;
                    dano = danoCausado (mobs, player, vet, r, spells, n);
                    mobs[vet[r]].hp -= dano;
                    cout << "Você causou " << dano << "de dano!";
                
                    cout << "O monstro te atacou de volta!" << endl;
                    dano = danoSofrido (mobs, player, vet, r, spells, n);
                    player.hp -= dano;
                    cout << "Você sofreu " << dano << "de dano!" << endl;

                    cout << "Seu HP: " << player.hp << "/" << player.hpmax << endl;
                    cout << "Sua Mana: " << player.mana << "/" << player.manamax << endl;
                    cout << "HP Mob: " << mobs[vet[r]].hp << "/" << mobs[vet[r]].hpmax << endl;
                }

                /* if (n == 2) { FAZER DEPOIS
                    cout << "Escolha um item para utilizar: "
                } */

            } else {
                cout << "O monstro é mais rápido que você! Você sofreu " << dano << "de dano!";
                dano = danoSofrido (mobs, player, vet, r, spells, n);
                player.hp -= dano;
                cout << "Você sofreu " << dano << "de dano!" << endl;
                cout << "Seu HP: " << player.hp << "/" << player.hpmax << endl;
                cout << "Sua Mana: " << player.mana << "/" << player.manamax << endl;
                
                cout << "Escolha uma opção para contra-atacar!" << endl;
                cout << "1- Atacar" << endl;
                cout << "2- Usar Item" << endl;
                cin >> n;

                if (n == 1) {
                    cout << "Escolha uma Habilidade:" << endl;
                    n = 0;

                    while (n < player.level) {
                        if (n == spells[n].id) {
                            cout << n+1 << "- " << spells[n].nome << endl;
                            n++;
                        }
                    }

                    cin >> n;

                    while (n > player.level or n <= 0) {
                        cout << "Você inseriu um valor inválido. Insira novamente." << endl;
                        cin >> n;
                    }

                    cout << "Você utilizou a habilidade " << spells[n-1].nome << endl;
                    dano = danoCausado(mobs, player, vet, r, spells, n);
                    mobs[vet[r]].hp -= dano;
                    cout << "Você causou " << dano << "de dano!" << endl;
                    cout << "Seu HP: " << player.hp << "/" << player.hpmax << endl;
                    cout << "Sua Mana: " << player.mana << "/" << player.manamax << endl;
                    cout << "HP Mob: " << mobs[vet[r]].hp << "/" << mobs[vet[r]].hpmax << endl;
                } /* else { // Usar Item - Fazer depois

                } */
            }
        }

        if (player.hp > 0) {
            cout << "Parabéns!!! Você derrotou com sucesso o " << mobs[vet[r]].nome << "!!!" << endl;
            player.xp += mobs[vet[r]].xp;
            cout << "Você adquiriu " << mobs[vet[r]].xp << " de xp!" << endl;
            gold = rand() % (mobs[vet[r]].gold +1);
            player.gold += gold;
            cout << "Você adquiriu " << gold << " de gold!" << endl;
            cout << "HP Restante: " << player.hp << "/" << player.hpmax << endl;
            cout << "Mana Restante: " << player.mana << "/" << player.manamax << endl;

            recarregarMonstro (mobs, vet, r);
            recarregarSpell (spells);
        } else {
            cout << "Hahahaha! Você morreu, noob!" << endl;
            cout << "Infelizmente a sua experiência foi zerada. Upe novamente" << endl;
            player.xp = 0;
            recarregarMonstro (mobs, vet, r);
            recarregarSpell (spells);
        }
    }
}

void sortearMonstro (monstro mobs[], personagem &player, int vetN[], int vetE[], int vetB[], habilidades spells[]) {
    unsigned seed = time(0);
    srand(seed);
    int random;
    random = 1 + rand() % 100;

    if (random == 100) {
        cout << "Parabéns, você encontrou um Boss!" << endl;
        random = 1 + rand()%2;
        vetB[random]; 
        batalha (mobs, player, vetB, random, spells);

    } else if (random > 90) {
        cout << "Parabéns, você encontrou um monstro Elite!" << endl;
        random = 1 + rand()%4;
        vetE[random];
        batalha (mobs, player, vetE, random, spells);

    } else {
        cout << "Parabéns, você encontrou um monstro Normal!" << endl;
        random = 1 + rand()%8;
        vetN[random];
        batalha (mobs, player, vetN, random, spells);
    }
}

void filtroMonstro (monstro mobs[], personagem &player, habilidades spells[]) {
    int vetN[8], vetE[4], vetB[2], n = 0, e = 0, b = 0;

    for (int i = 0; i < 8; i++) {
        vetN[i] = -1;
    }

    for (int i = 0; i < 4; i++) {
        vetE[i] = -1;
    }

    for (int i = 0; i < 2; i++) {
        vetB[i] = -1;
    }

    for (int i = 0; i < 140; i++) { // Alterar a quantidade aqui de acordo com o número total de monsstros
        if (mobs[i].level == player.level and mobs[i].tipo == 1) {
            vetN[n] = mobs[i].id;
            n++;
        } else if (mobs[i].level == player.level and mobs[i].tipo == 2) {
            vetE[e] = mobs[i].id;
            e++;
        } else if (mobs[i].level == player.level and mobs[i].tipo == 4) {
            vetB[b] = mobs[i].id;
            b++;
        }
    }

    sortearMonstro (mobs, player, vetN, vetE, vetB, spells);
} 

int menu (int &numero, personagem &player, monstro mobs[], habilidades spells[]) { // menu de 1 a 8
        switch (numero) {
        case 1: // Personagem
            visualizarPersonagem(numero, player);
            return 0;
            break;
        case 2: // Lutar
            filtroMonstro (mobs, player, spells);
            return 0;
            break;
        case 3: // Loja
            return 0;
            break;
        case 4: // Ferreiro
            return 0;
            break;
        case 5: // Curar
            curar (player);
            return 0;
            break;
        case 6: // Salvar Progresso;
            exportar (player);
            return 0;
            break;
        case 7: // sair
            return 7;
            break;
    }

    return 0;
}

int main () {
    personagem player;
    monstro mobs[140]; // alterar conforme crescer os monstros
    int vezes = 0;
    habilidades spells[10];
    ifstream character ("personagem.txt");

    if (character) {
        character >> player.nome >> player.hp >> player.hpmax >> player.mana >> player.manamax >> player.atk >> player.def >> player.forca >> player.agil >> player.intel >> player.resis >> player.xp >> player.level >> player.gold >> player.pontos;
        cout << "Bem vindo novamente " << player.nome << "!" << endl;
        character.close();
    } else {
        cout <<  "Bem vindo, novo jogador! Insira seu nome de usuário: ";
        getline (cin, player.nome);
        player.hp = 0;
        player.hpmax = 0;
        player.mana = 0;
        player.manamax = 0;
        player.atk = 0;
        player.def = 0;
        player.forca = 3;
        player.agil = 3;
        player.intel = 3;
        player.resis = 3;
        player.xp = 0;
        player.level = 1;
        player.gold = 0;
        player.pontos = 0;
        status (player);
        player.hp = player.hpmax;
        player.mana = player.manamax;
        ofstream saida ("personagem.txt");
        saida << player.nome << endl << player.hp << player.hpmax << endl << player.mana << player.manamax << endl << player.atk << endl << player.def << endl << player.forca << endl << player.agil << endl << player.intel << endl << player.resis << endl << player.xp << endl << player.level << endl << player.gold << endl << player.pontos << endl;
        saida.close(); 
        cout << "Seu personagem foi criado com sucesso!" << endl;
    }

    ifstream monsters ("mobs.txt");

    if (monsters) {
        
        for (int i = 0; i < 140; i++) { // alterar a quantidade de monstros aqui
            monsters >> mobs[i].id >> mobs[i].tipo >> mobs[i].level >> mobs[i].nome >> mobs[i].hp >> mobs[i].hpmax >> mobs[i].mana >> mobs[i].manamax >> mobs[i].atk >> mobs[i].def >> mobs[i].forca >> mobs[i].agil >> mobs[i].intel >> mobs[i].resis >> mobs[i].xp >> mobs[i].gold;
        }
        
        statusMonstros (mobs);
        cout << "Os monstros foram carregados com sucesso! Pronto para batalhar!" << endl;
        monsters.close();
    } else {
        cout << "Deu erro ao carregar os monstros. Fale com o Ryhan para consertar isso, seu filho da puta!" << endl;
    }

    ifstream habilidade ("habilidades.txt");
    
    if (habilidade) {
        for (int i = 0; i < 10; i++) {
            habilidade >> spells[i].id >> spells[i].nome >> spells[i].golpes >> spells[i].multiplicador >> spells[i].custo >> spells[i].redDef >> spells[i].redDano >> spells[i].cura >> spells[i].cd >> spells[i].cdAtual >> spells[i].buff;
        }
        cout << "As Habilidades foram carregadas com sucesso!" << endl;
        habilidade.close();
    } else {
        cout << "Deu erro ao carregar as habilidades. Fale com o Ryhan para consertar isso, seu filho da puta!" << endl;
    }
    int numero = 0;
    
    while (numero < 7) { // inserir o menu até sair do programa inserindo 7
        cout << "Insira um número de 1 a 7 de acordo com o Menu:" << endl;
        cout << "1 - Personagem" << endl;
        cout << "2 - Batalhar" << endl;
        cout << "3 - Loja" << endl;
        cout << "4 - Ferreiro" << endl;
        cout << "5 - Curar" << endl;
        cout << "6 - Salvar Progresso" << endl;
        cout << "7 - Sair" << endl;
        cin >> numero;
        menu (numero, player, mobs, spells);
    }

    cout << "Saindo... Não esqueça de dar o feedback ao Ryhan!" << endl;

    return 0;
}