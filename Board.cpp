#include <iostream>
#include <utility>
#include <map>
#ifndef _WIN32
#include "Terminal.h"
#endif // !_WIN32
#include "Board.h"
#include "CreatePiece.h"
#include "Exceptions.h"
#include <string>

using std::string;
using std::string::at;

namespace Chess
{
  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  Board::Board(){}

  const Piece* Board::operator()(const Position& position) const {
    if (occ[position] == nullptr) {
      return NULL;
    }
    return occ[position];
  }
  
  void Board::add_piece(const Position& position, const char& piece_designator) {

    string valid_piece_designators = "KkQqBbNnRrPpMm";
    bool valid_designator = false;
    bool valid_position = false;
    bool piece_exists = false;

    // updates valid_designator if applicable
    for (int i = 0; i < valid_piece_designators.length(); i++) {
      if (piece_designator.compare(valid_piece_designators.at(i)) == 0) {
        valid_designator = true;
        break;
      }
    }

    // updates valid_position if applicable
    if ((position.first >= 'A' && position.first <= 'H') && (position.second >= '1' && position.second <= '8')) {
      valid_position = true;
    }

    // updates no_piece_exists if applicable
    if ((*this)(position) != nullptr) {
      piece_exists = true;
    }

    // throws exceptions if necessary
    if (!valid_designator) {
      throw Exception("invalid designator");
    }
    if (!valid_position) {
      throw Exception("invalid position");
    }
    if (piece_exists) {
      throw Exception("position is occupied");
    }

    // updates map if an exception is not thrown
    occ[position] = create_piece(piece_designator);
  }

  void Board::display() const {
    //Setting Background Color

	color_bg(bright, MAGENTA);

	//Setting Foreground Color

	color_fg(bright, BLACK);

	//TODO: Ask in Office Hours what exactly to do here :)
  }

  std::map<Position, Piece*> Board::get_occ() const {
    return occ;
  }
  
  bool Board::has_valid_kings() const {
    int white_king_count = 0;
    int black_king_count = 0;
    for (std::map<std::pair<char, char>, Piece*>::const_iterator it = occ.begin();
	 it != occ.end();
	 it++) {
      if (it->second) {
	switch (it->second->to_ascii()) {
	case 'K':
	  white_king_count++;
	  break;
	case 'k':
	  black_king_count++;
	  break;
	}
      }
    }
    return (white_king_count == 1) && (black_king_count == 1);
  }

  /////////////////////////////////////
  // DO NOT MODIFY THIS FUNCTION!!!! //
  /////////////////////////////////////
  std::ostream& operator<<(std::ostream& os, const Board& board) {
    for(char r = '8'; r >= '1'; r--) {
      for(char c = 'A'; c <= 'H'; c++) {
	const Piece* piece = board(Position(c, r));
	if (piece) {
	  os << piece->to_ascii();
	} else {
	  os << '-';
	}
      }
      os << std::endl;
    }
    return os;
  }
}
