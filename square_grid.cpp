#include "square_grid.h"

SquareGrid::SquareGrid(float x_in, float y_in, float w_in, const char *position_file_name) : ElementSquareShape(x_in, y_in, w_in)
{
    char aux_char;
    char aux_str[5];
    bool flag = true;
    bool error = false;
    uint8_t i = 0, j = 0;

    FILE *position_file = fopen(position_file_name, "r");

    kings_positions[white] = Coord::none;
    kings_positions[black] = Coord::none;

    last_selected = Coord::none;

    while (flag && !error) // flag indicates when the program is done reading the pieces positions
    {
        aux_char = (char)fgetc(position_file);
        if (isalpha(aux_char))
        {
            grid[i][j] = new Square(i * w_in / 8, j * w_in / 8, w_in / 8, aux_char, i, j);
            if (aux_char == 'K')
                kings_positions[white].setCoord(i, j);
            if (aux_char == 'k')
                kings_positions[black].setCoord(i, j);
            i++;
        }
        else if (isdigit(aux_char))
        {
            for (int k = i + aux_char - '0'; i < k; i++)
                grid[i][j] = new Square(i * w_in / 8, j * w_in / 8, w_in / 8, aux_char, i, j);
        }
        else if (aux_char == '/')
        {
            if (i != 8)
                error = true;
            else
            {
                i = 0;
                j++;
            }
        }
        else if (isspace(aux_char))
        {
            if (j != 7)
            {
                error = true;
            }
            flag = false;
        }
        else
        {
            error = true;
        }
    }

    if (!error)
    {
        printf("Matriz de piezas armada.\n");
        fscanf(position_file, "%s", aux_str);
        if (strlen(aux_str) != 1)
        {
            error = true;
        }
        else if (aux_str[0] != 'w' && aux_str[0] != 'b')
        {
            error = true;
        }
        else
        {
            now_turn = (aux_str[0] == 'w') ? white : black;
        }
    }

    if (!error)
    {
        printf("Turno actual cargado.\n");
        castling.priviledge[kingside][white] = false;
        castling.priviledge[queenside][white] = false;
        castling.priviledge[kingside][black] = false;
        castling.priviledge[queenside][black] = false;

        fscanf(position_file, "%s", aux_str);

        i = 0;
        flag = false; // flag indicates if there was a '-', in that case no more characters can be read, else error
        for (; aux_str[i] != '\0' && !error; i++)
        {
            if (flag)
            {
                error = true;
            }
            else
            {
                switch (aux_str[i])
                {
                case 'K':
                    if (grid[4][7]->getPiece()->getType() == king && grid[7][7]->getPiece()->getType() == rook &&
                        grid[4][7]->getPiece()->getTeam() == white && grid[7][7]->getPiece()->getTeam() == white &&
                        !castling.priviledge[kingside][white])
                    {
                        castling.priviledge[kingside][white] = true;
                    }
                    else
                        error = true;
                    break;
                case 'k':
                    if (grid[4][0]->getPiece()->getType() == king && grid[7][0]->getPiece()->getType() == rook &&
                        grid[4][0]->getPiece()->getTeam() == black && grid[7][0]->getPiece()->getTeam() == black &&
                        !castling.priviledge[kingside][black])
                    {
                        castling.priviledge[kingside][black] = true;
                    }
                    else
                        error = true;
                    break;
                case 'Q':
                    if (grid[4][7]->getPiece()->getType() == king && grid[0][7]->getPiece()->getType() == rook &&
                        grid[4][7]->getPiece()->getTeam() == white && grid[0][7]->getPiece()->getTeam() == white &&
                        !castling.priviledge[queenside][white])
                    {
                        castling.priviledge[queenside][white] = true;
                    }
                    else
                        error = true;
                    break;
                case 'q':
                    if (grid[4][0]->getPiece()->getType() == king && grid[0][0]->getPiece()->getType() == rook &&
                        grid[4][0]->getPiece()->getTeam() == black && grid[0][0]->getPiece()->getTeam() == black &&
                        !castling.priviledge[queenside][black])
                    {
                        castling.priviledge[queenside][black] = true;
                    }
                    else
                        error = true;
                    break;
                case '-':
                    if (i != 0)
                    {
                        error = true;
                    }
                    else
                    {
                        flag = true;
                    }
                    break;
                default:
                    error = true;
                    break;
                }
            }
        }
        if (i > 5)
        {
            error = true;
        }
    }

    if (!error)
    {
        printf("Privilegios de enroque cargados.\n");
        fscanf(position_file, "%s", aux_str);

        if (aux_str[0] == '-' && aux_str[1] == '\0')
        {
            en_passant = Coord::none;
        }
        else if ((aux_str[1] >= 'a' && aux_str[1] <= 'h') && (aux_str[1] >= '1' && aux_str[1] <= '8') && aux_str[2] == '\0')
        {
            en_passant.x = aux_str[0] - 'a';
            en_passant.y = aux_str[1] - 7 - '1';
        }
        else
        {
            error = true;
        }
    }

    if (!error)
    {
        printf("Coordenadas de en passant cargadas.\n");
        fscanf(position_file, "%ud", &half_moves);
        fscanf(position_file, "%ud", &full_moves);
        printf("Contador de movimientos cargado.\n");
    }

    if (error)
    {
        printf("Error leyendo archivo de posición.\n");
        exit(-1);
    }
    else
    {
        printf("Archivo de posición leído correctamente.\n");
    }

    fclose(position_file);
}

SquareGrid::~SquareGrid()
{
    for (uint8_t i = 0; i < 8; i++)
        for (uint8_t j = 0; j < 8; j++)
            delete grid[i][j];
}

void SquareGrid::clicked(float x_in, float y_in)
{
    Coord in((uint8_t)(8 * (x_in - x) / w), (uint8_t)(8 * (y_in - y) / w));
    if (grid[in.x][in.y]->isWithinThis(x_in, y_in))
    {
        switch (grid[in.x][in.y]->getHighlight())
        {
        case selected:
            break;
        case blank:
        case used:
            clearHighlight();
            if(grid[in.x][in.y]->getPiece()->getTeam() == now_turn)
            {
                highlightPathOfThis(in);
            }
            grid[in.x][in.y]->setHighlight(selected);
            last_selected = in;
            break;
        case valid:
        case pawn_double:
        case pawn_promotes:
        case passant:
        case castles:
            clearHighlight();
            genericMoveMade(last_selected, in);
            break;
        }
    }
}

void SquareGrid::draw(float x_origin, float y_origin) const
{
    for (uint8_t i = 0; i < 8; i++)
        for (uint8_t j = 0; j < 8; j++)
            grid[i][j]->draw(x + x_origin, y + y_origin);
}

void SquareGrid::updateSizeAndPosition(float x_in, float y_in, float w_in)
{
    updateSize(w_in);
    updatePosition(x_in, y_in);
    for (uint8_t i = 0; i < 8; i++)
        for (uint8_t j = 0; j < 8; j++)
            grid[i][j]->updateSizeAndPosition(i * w / 8, j * w / 8, w / 8);
}

/* Movement validation */

bool SquareGrid::can1stMoveTo2nd(Coord first, Coord second)
{
    Piece *aux_ptr;
    bool ret = false;
    teams team_moving_piece = grid[first.x][first.y]->getPiece()->getTeam();

    if (first.isValid() && second.isValid())
    {
        if (grid[first.x][first.y]->getPiece() != nullptr)
        {
            if (grid[second.x][second.y]->getPiece() == nullptr ||
                grid[second.x][second.y]->getPiece()->getTeam() != team_moving_piece)
            {
                /* Exchange pieces */
                if (grid[first.x][first.y]->getPiece()->getType() == king)
                {
                    kings_positions[team_moving_piece] = second;
                }
                aux_ptr = grid[second.x][second.y]->getPiece();
                grid[second.x][second.y]->setPiece(grid[first.x][first.y]->getPiece());
                grid[first.x][first.y]->setPiece(nullptr);

                ret = !isCheckAgainstThis(team_moving_piece);

                /* Undo exchange pieces */
                if (grid[second.x][second.y]->getPiece()->getType() == king)
                {
                    kings_positions[team_moving_piece] = first;
                }
                grid[first.x][first.y]->setPiece(grid[second.x][second.y]->getPiece());
                grid[second.x][second.y]->setPiece(aux_ptr);
            }
        }
    }

    return ret;
}

bool SquareGrid::isCheckAgainstThis(teams team)
{
    Coord target;
    bool ret = false;

    for (uint8_t dir = 0; dir < 4 && !ret; dir++)
    {
        uint16_t flags_for_stop = bishop | knight | rook;

        for (uint8_t i = 0; i < 8 && !ret; i++)
        {
            for (uint8_t j = 0; j < 7 && !ret; j++)
            {
                switch (dir)
                {
                case 0:
                    target = getCoord(kings_positions[team].x + i, kings_positions[team].y + j + 1);
                    break;
                case 1:
                    target = getCoord(kings_positions[team].x - j - 1, kings_positions[team].y + i);
                    break;
                case 2:
                    target = getCoord(kings_positions[team].x - i, kings_positions[team].y - j - 1);
                    break;
                case 3:
                    target = getCoord(kings_positions[team].x + j + 1, kings_positions[team].y - i);
                    break;
                }

                if (target.isValid())
                {
                    if (grid[target.x][target.y]->getPiece() != nullptr)
                    {
                        if (grid[target.x][target.y]->getPiece()->getTeam() != team)
                        {
                            if (SquareGridUtils::movement_matrix[i][j] & grid[target.x][target.y]->getPiece()->getType() & flags_for_stop)
                            {
                                ret = true;
                            }
                        }
                        if (SquareGridUtils::movement_matrix[i][j] & bishop & flags_for_stop)
                        {
                            flags_for_stop &= ~(bishop);
                        }
                        if (SquareGridUtils::movement_matrix[i][j] & rook & flags_for_stop)
                        {
                            flags_for_stop &= ~(rook);
                        }
                    }
                }
            }
        }
    }

    if (!ret)
    {
        int8_t add_to_y = (team == white) ? -1 : 1;
        for (int8_t add_to_x = -1; add_to_x <= 1; add_to_x += 2)
        {
            target = getCoord(kings_positions[team].x + add_to_x, kings_positions[team].y + add_to_y);
            if (target.isValid())
            {
                if (grid[target.x][target.y]->getPiece() != nullptr)
                {
                    if (grid[target.x][target.y]->getPiece()->getTeam() != team)
                    {
                        if (grid[target.x][target.y]->getPiece()->getType() == pawn)
                        {
                            ret = true;
                        }
                    }
                }
            }
        }
    }

    return ret;
}

bool SquareGrid::isCheckAgainstOther(teams team) { return isCheckAgainstThis((team == white) ? black : white); }

bool SquareGrid::areMovesAvailableForThis(teams team)
{
    Coord target;
    bool ret = false;

    ret = highlightPathOfThis(kings_positions[team]);
    for (uint8_t i = 0; i < 8 && !ret; i++)
    {
        for (uint8_t j = 0; j < 8 && !ret; j++)
        {
            if(grid[i][j]->getPiece()->getTeam() == team && !(getCoord(i, j) == kings_positions[team]))
            {
                target = getCoord(i, j);
                ret = highlightPathOfThis(target);
            }
        }
    }

    return ret;
}

bool SquareGrid::areMovesAvailableForOther(teams team) { return areMovesAvailableForThis((team == white) ? black : white); }

/* Movement */

void SquareGrid::genericMoveMade(Coord &first, Coord &second)
{
    bool moves_available;
    bool checkmate;

    grid[second.x][second.y]->setPiece(grid[first.x][first.y]->getPiece());
    grid[second.x][second.y]->setHighlight(used);
    grid[first.x][first.y]->setPiece(nullptr);
    grid[first.x][first.y]->setHighlight(used);

    /* are there any moves available for the other team */
    moves_available = areMovesAvailableForOther(now_turn);

    /* Is the move checkmate */
    checkmate = isCheckAgainstOther(now_turn);

    now_turn = (now_turn == white) ? black : white;
}