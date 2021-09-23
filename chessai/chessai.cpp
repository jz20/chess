#include <torch/torch.h>
#include <vector>
#include <string>
#include <iostream>
#include <random>
#include <unordered_map>

#include <game.h>
#include <chessgame.h>

using namespace torch;
using namespace std;

#define GLOBAL 15
#define PIECE_CENTRIC 170
#define SQUARE_CENTRIC 128
// implement these before trying to do training
#define TOTAL 313

#define TOTAL_PIECES 32

// I think I should not use convolution layers because the input space consists
// of "sharp edges" like when the data switches from representing information
// about a queen to that about a knight

// Linear layers seem to be a decent starting point

// It seems that parameterise the game everytime is a waste of time because the
// majority of the parameters won't change but I don't know what a good way to
// detect the unchanged parameters without redoing all the work is

#define V_EMPTY 2.7
#define V_KING 1.8
#define V_QUEEN 0.9
#define V_ROOK 0.5
#define V_BISHOP 0.31
#define V_KNIGHT 0.3
#define V_PAWN 0.1

double avgLoss;

unordered_map <Square *, double> attackMap;
unordered_map <Square *, double> defendMap;
vector <Piece *> pieceList;
void setUpMaps(Game *game);
void updateMaps(Game *game);
void setUpPieceList(Game *game);

vector <Tensor> parameterise(Game *game);
vector <double> parseGlobal(Game *game);
vector <double> parsePiece(Game *game);
vector <double> parseSquare(Game *game);
double heuristic(Game *game);

struct EvaluatorImpl : nn::Module {
    EvaluatorImpl():
        global(nn::LinearOptions(GLOBAL, GLOBAL)), 
        piece_centric(nn::LinearOptions(PIECE_CENTRIC, PIECE_CENTRIC)), 
        square_centric(nn::LinearOptions(SQUARE_CENTRIC, SQUARE_CENTRIC)), 
        second(nn::LinearOptions(TOTAL, 100)), 
        third(nn::LinearOptions(100, 1)) {
            register_module("global", global);
            register_module("piece_centric", piece_centric);
            register_module("square_centric", square_centric);
            register_module("second", second);
            register_module("third", third);
    }
    Tensor forward(Tensor global_tensor, Tensor piece_tensor, Tensor square_tensor) {
        // cout << global_tensor << endl;
        global_tensor = relu(global(global_tensor));
        // cout << global_tensor << endl;
        // cout << piece_tensor << endl;
        piece_tensor = relu(piece_centric(piece_tensor));
        // cout << piece_tensor << endl;
        // cout << square_tensor << endl;
        square_tensor = relu(square_centric(square_tensor));
        // cout << square_tensor << endl;
        Tensor total = torch::cat({global_tensor, piece_tensor, square_tensor}, 0);
        // cout << total << endl;
        total = relu(second(total));
        // cout << total << endl;
        total = tanh(third(total));
        cout << total << endl;
        return total;
    }
    nn::Linear global, piece_centric, square_centric, second, third;
};
TORCH_MODULE(Evaluator);

#define POINT cout << count << endl; count++;

struct ChessBot {
    Game *game;
    Evaluator evaluator;
    bool white;

    ChessBot(Game *game, Evaluator evaluator, bool white) {
        this->game = game;
        this->evaluator = evaluator;
        this->white = white;
    }
    void makeMove() {
        game->updateMoves();
        vector <GameMove> moves = game->getMoves();
        double best = -1;
        GameMove *select = NULL;
        int tiedBest = 0;
        double total_loss = 0;
        int n = 0;
        for (auto it = moves.begin(); it != moves.end(); it++) {
            game->tryMove(*it);
            vector <Tensor> data = parameterise(game);

            evaluator->zero_grad();
            Tensor t_eval = evaluator->forward(data[0], data[1], data[2]); // AA
            double eval = t_eval.item().toDouble();
            double target = heuristic(game);
            // if (!white) {
            //     exit(0);
            //     eval = -eval;
            //     t_eval = torch::full({1}, eval);
                
            //     target = -target;
            // }
                
            Tensor t_target = torch::full({1}, target); // AA
            // cout << eval << "," << target << endl;
            Tensor d_loss = l1_loss(t_eval, t_target); // AA
        // cout << eval << ", " << target << ", " << d_loss.item().toDouble() << endl;
        // ofstream file("training.log", ios_base::app);
        // file << d_loss.item().toDouble() << endl;
            total_loss += d_loss.item().toDouble(); // AA
            n++;
            // try l2
            d_loss.backward();
            if (eval > best) {
                select = &*it;
                best = eval;
                tiedBest = 1;
            }
            if (eval == best) {
                tiedBest++;
                if ((float) rand() / (float) RAND_MAX < (float) 1 / (float) tiedBest) {
                    select = &*it;
                    best = eval;
                }
            }
            game->reverseLast();
        }
        avgLoss += (n != 0) ? (total_loss / n) : 0;
        game->tryMove(*select);
    }
};

int main() {
    

    Evaluator evaluator;
    
    optim::Adam evaluator_optimiser(evaluator->parameters(), optim::AdamOptions().lr(0.01));
    
    // cout << evaluator->parameters() << endl;
    // if () {
        // load(evaluator, "evaluator.pt");
        // load(evaluator_optimiser, "evaluator_optimiser.pt");
    // }
    // cout << evaluator->parameters() << endl;
    // exit(0);

    for (int i = 0; i < 2000; i++) {
        // cout << i << endl;
        Game *game = new ChessGame();
        game->setUp();
        setUpMaps(game);
        setUpPieceList(game);
        avgLoss = 0;
        int avgOver = 0; 

        ChessBot whiteBot = ChessBot(game, evaluator, true);
        ChessBot blackBot = ChessBot(game, evaluator, false);    
        
        // cout << game->getBoard()->snapshot() << endl;
        bool result = false;
        int c = 0;
        while (!game->isFinished()) {
            updateMaps(game);
            whiteBot.makeMove();
            avgOver++;
            result = game->checkResult();

            evaluator_optimiser.step();

            if (i % 100 == 0) {
                cout << game->getBoard()->snapshot() << endl;
                ofstream file("games.log", ios_base::app);
                file << ((avgOver != 0) ? (avgLoss / avgOver) : -1) << endl;
            }
            if (game->isFinished()) {
                break;
            }
            updateMaps(game);
            blackBot.makeMove();
            avgOver++;
            result = game->checkResult();

            evaluator_optimiser.step();
            
            if (i % 20 == 0) {
                cout << game->getBoard()->snapshot() << endl;
                ofstream file("games.log", ios_base::app);
                file << ((avgOver != 0) ? (avgLoss / avgOver) : -1) << endl;
            }

            if (c == 5) {
                exit(0);
            }
            c++;
        }
        if (result) {
            cout << "win\n";
        } else {
            cout << "draw\n";
        }
        cout << "loss: " << ((avgOver != 0) ? (avgLoss / avgOver) : -1) << endl;
        ofstream file("training.log", ios_base::app);
        file << ((avgOver != 0) ? (avgLoss / avgOver) : -1) << endl;

        // Print values
        // for (const auto& p : evaluator->named_parameters()) {
        //     cout << p.key() << ": " << p.value() << endl;
        // }

        if (i % 20 == 0) {
            save(evaluator, "evaluator.pt");
            save(evaluator_optimiser, "evaluator_optimiser.pt");
        }
    }

    return 0;
}

vector <Tensor> parameterise(Game *game) {
    vector <Tensor> tensors;
    
    vector <double> v_global = parseGlobal(game);
    Tensor global = torch::from_blob(v_global.data(), {GLOBAL}, TensorOptions().dtype(kFloat64)).to(kFloat32);

    vector <double> v_piece = parsePiece(game);
    Tensor piece = torch::from_blob(v_piece.data(), {PIECE_CENTRIC}, TensorOptions().dtype(kFloat64)).to(kFloat32);

    vector <double> v_square = parseSquare(game);
    Tensor square = torch::from_blob(v_square.data(), {SQUARE_CENTRIC}, TensorOptions().dtype(kFloat64)).to(kFloat32);
    tensors.push_back(global);
    tensors.push_back(piece);
    tensors.push_back(square);
    // TODO
    return tensors;
}

vector <double> parseGlobal(Game *game) {
    vector <double> v_global;
    bool white_turn = game->getCurrentPlayer()->getColour() == WHITE;
    Player *white = white_turn ? game->getCurrentPlayer() : game->getOppositePlayer();
    Player *black = white_turn ? game->getOppositePlayer() : game->getCurrentPlayer();
    // side to move
    if (white_turn) {
        v_global.push_back(1);
    } else {
        v_global.push_back(-1);
    }
    // castle rights
    v_global.push_back(game->getTrackers()[WLC]);
    v_global.push_back(game->getTrackers()[WSC]);
    v_global.push_back(game->getTrackers()[BLC]);
    v_global.push_back(game->getTrackers()[BSC]);
    // material configuration
    enum PieceType {WQ, WR, WB, WN, WP, BQ, BR, BB, BN, BP, NUM_PieceType};
    vector <double> pieceCount(NUM_PieceType, 0);

    vector <Piece *> whitePieces = white->getPieces();
    for (auto it = whitePieces.begin(); it != whitePieces.end(); it++) {
        string name = (*it)->getName();
        if (name == "queen") {
            pieceCount[WQ]++;
        } else if (name == "rook") {
            pieceCount[WR]++;
        } else if (name == "bishop") {
            pieceCount[WB]++;
        } else if (name == "knight") {
            pieceCount[WN]++;
        } else if (name == "pawn") {
            pieceCount[WP]++;
        }
    }

    vector <Piece *> blackPieces = black->getPieces();
    for (auto it = blackPieces.begin(); it != blackPieces.end(); it++) {
        string name = (*it)->getName();
        if (name == "queen") {
            pieceCount[BQ]++;
        } else if (name == "rook") {
            pieceCount[BR]++;
        } else if (name == "bishop") {
            pieceCount[BB]++;
        } else if (name == "knight") {
            pieceCount[BN]++;
        } else if (name == "paBn") {
            pieceCount[BP]++;
        }
    }

    v_global.insert(v_global.end(), pieceCount.begin(), pieceCount.end());

    return v_global;
}

vector <double> parseSquare(Game *game) {
    vector <double> v_square;
    Board *board = game->getBoard();
    for (int i = 0; i < board->getRows(); i++) {
        for (int j = 0; j < board->getCols(); j++) {
            v_square.push_back(attackMap[board->getSquare(i, j)]);
            v_square.push_back(defendMap[board->getSquare(i, j)]);
        }
    }
    return v_square;
}

void setUpPieceList(Game *game) {
    Board *board = game->getBoard();
    pieceList.push_back(board->getSquare(0, 4)->getPiece());
    pieceList.push_back(board->getSquare(0, 3)->getPiece());
    pieceList.push_back(board->getSquare(0, 0)->getPiece());
    pieceList.push_back(board->getSquare(0, 7)->getPiece());
    pieceList.push_back(board->getSquare(0, 2)->getPiece());
    pieceList.push_back(board->getSquare(0, 5)->getPiece());
    pieceList.push_back(board->getSquare(0, 1)->getPiece());
    pieceList.push_back(board->getSquare(0, 6)->getPiece());
    for (int i = 0; i < board->getCols(); i++) {
        pieceList.push_back(board->getSquare(1, i)->getPiece());
    }
    pieceList.push_back(board->getSquare(7, 4)->getPiece());
    pieceList.push_back(board->getSquare(7, 3)->getPiece());
    pieceList.push_back(board->getSquare(7, 0)->getPiece());
    pieceList.push_back(board->getSquare(7, 7)->getPiece());
    pieceList.push_back(board->getSquare(7, 2)->getPiece());
    pieceList.push_back(board->getSquare(7, 5)->getPiece());
    pieceList.push_back(board->getSquare(7, 1)->getPiece());
    pieceList.push_back(board->getSquare(7, 6)->getPiece());
    for (int i = 0; i < board->getCols(); i++) {
        pieceList.push_back(board->getSquare(6, i)->getPiece());
    }
}

void setUpMaps(Game *game) {
    Board *board = game->getBoard();
    for (int i = 0; i < board->getRows(); i++) {
        for (int j = 0; j < board->getCols(); j++) {
            attackMap[board->getSquare(i, j)] = V_EMPTY;
            defendMap[board->getSquare(i, j)] = V_EMPTY;
        }
    }
}

void updateMaps(Game *game) {
    // update attack map
    for (auto kv : attackMap) {
        attackMap[kv.first] = V_EMPTY;
    }
    Player *attacker = game->getCurrentPlayer();
    vector <Piece *> attackingPieces = attacker->getPieces();
    for (Piece *piece : attackingPieces) {
        if (piece->getSquare() != NULL) {
            piece->updateTargets(true);
            vector <Square *> squares = piece->getTargets();
            double value = V_EMPTY;
            string name = piece->getName();
            if (name == "king") { value = V_KING; } else if (name == "queen") { value = V_QUEEN; } 
                    else if (name == "rook") { value = V_ROOK; } else if (name == "bishop") { value = V_BISHOP; } 
                    else if (name == "knight") { value = V_KNIGHT; } else if (name == "pawn") { value = V_PAWN; }
            for (Square *square : squares) {
                if (attackMap[square] > value) {
                    attackMap[square] = value;
                }
            }
        }
    }
    // update defend map
    for (auto kv : defendMap) {
        defendMap[kv.first] = V_EMPTY;
    }
    Player *defender = game->getOppositePlayer();
    vector <Piece *> defendingPieces = defender->getPieces();
    for (Piece *piece : defendingPieces) {
        if (piece->getSquare() != NULL) {
            piece->updateTargets(true);
            vector <Square *> squares = piece->getTargets();
            double value = V_EMPTY;
            string name = piece->getName();
            if (name == "king") { value = V_KING; } else if (name == "queen") { value = V_QUEEN; } 
                    else if (name == "rook") { value = V_ROOK; } else if (name == "bishop") { value = V_BISHOP; } 
                    else if (name == "knight") { value = V_KNIGHT; } else if (name == "pawn") { value = V_PAWN; }
            for (Square *square : squares) {
                if (defendMap[square] > value) {
                    defendMap[square] = value;
                }
            }
        }
    }
}

double heuristic(Game *game) {
    bool white_turn = game->getCurrentPlayer()->getColour() == WHITE;
    Player *white = white_turn ? game->getCurrentPlayer() : game->getOppositePlayer();
    Player *black = white_turn ? game->getOppositePlayer() : game->getCurrentPlayer();
    bool result = game->checkResult();
    if (game->isFinished()) {
        if (result) {
            game->setFinished(false);
            return white_turn ? -1 : 1;
        }
        game->setFinished(false);
        return 0;
    }

    double white_pv = 0;
    double black_pv = 0;
    vector <Piece *> whitePieces = white->getPieces();
    for (auto it = whitePieces.begin(); it != whitePieces.end(); it++) {
        if ((*it)->getSquare() != NULL) {
            string name = (*it)->getName();
            if (name == "queen") {
                white_pv += V_QUEEN;
            } else if (name == "rook") {
                white_pv += V_ROOK;
            } else if (name == "bishop") {
                white_pv += V_BISHOP;
            } else if (name == "knight") {
                white_pv += V_KNIGHT;
            } else if (name == "pawn") {
                white_pv += V_PAWN;
            }
        }
    }

    vector <Piece *> blackPieces = black->getPieces();
    for (auto it = blackPieces.begin(); it != blackPieces.end(); it++) {
        if ((*it)->getSquare() != NULL) {
            string name = (*it)->getName();
            if (name == "queen") {
                black_pv += V_QUEEN;
            } else if (name == "rook") {
                black_pv += V_ROOK;
            } else if (name == "bishop") {
                black_pv += V_BISHOP;
            } else if (name == "knight") {
                black_pv += V_KNIGHT;
            } else if (name == "pawn") {
                black_pv += V_PAWN;
            }
        }
    }
    // when does tanh reach 1
    double moveBonus = game->getMoves().size() * 0.02;
    if (white_turn) {
        white_pv += moveBonus;
    } else {
        black_pv += moveBonus;
    }
    return tanh(white_pv - black_pv);
}

vector <double> parsePiece(Game *game) {
    vector <double> v_piece;
    enum PiecePos {WK0, WQ0, WR0, WR1, WB0, WB1, WN0, WN1,
            WP0, WP1, WP2, WP3, WP4, WP5, WP6, WP7,
            BK0, BQ0, BR0, BR1, BB0, BB1, BN0, BN1,
            BP0, BP1, BP2, BP3, BP4, BP5, BP6, BP7, NUM_PiecePos};
    int numInfo = 4;
    for (int i = 0; i < NUM_PiecePos; i++) {
        if (pieceList[i] != NULL && pieceList[i]->getSquare() != NULL) {
            v_piece.push_back(1);
            Square *square = pieceList[i]->getSquare();
            v_piece.push_back(square->getRow());
            v_piece.push_back(square->getCol());
            v_piece.push_back(attackMap[square]);
            v_piece.push_back(defendMap[square]);
            if (i == WQ0 || i == WR0 || i == WR1 || i == WB0 || i == WB1
                    || i == BQ0 || i == BR0 || i == BR1 || i == BB0 || i == BB1) {
                pieceList[i]->updateTargets();
                v_piece.push_back(pieceList[i]->getTargets().size());
            }
        } else {
            v_piece.push_back(1);
            for (int j = 0; j < numInfo; j++) {
                v_piece.push_back(-1);
            }
            if (i == WQ0 || i == WR0 || i == WR1 || i == WB0 || i == WB1
                    || i == BQ0 || i == BR0 || i == BR1 || i == BB0 || i == BB1) {
                v_piece.push_back(-1);
            }
        }
    }
    return v_piece;
}