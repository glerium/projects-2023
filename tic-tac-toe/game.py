import numpy as np

class Table:
    def __init__(self) -> None:
        self.table = np.zeros((3,3), dtype=np.int16)
        self.full = False

    def get_piece(self, row, col) -> str:
        piece = self.table[row, col]
        if piece == 0:
            return '  '
        elif piece <= 9:
            return 'O' + str(piece)
        else:
            return 'X' + str(piece - 9)

    def put_piece(self, row, col, player, num) -> bool:
        if self.table[row, col] == 0:
            self.table[row, col] = player * 9 + num
            return True
        elif num > self.table[row, col]:
            self.table[row, col] = player * 9 + num
            return True
        else:
            return False
    
    def check_win(self, player) -> bool:
        def _player0(piece) -> bool:
            return piece > 0 and piece <= 9

        def _player1(piece) -> bool:
            return piece > 9

        got = False
        if player == 0:
            check = _player0
        else:
            check = _player1
        
        for i in range(3):
            ok = True
            for j in range(3):
                if not check(self.table[i, j]):
                    ok = False
                    break
            got |= ok

        for i in range(3):
            ok = True
            for j in range(3):
                if not check(self.table[j, i]):
                    ok = False
                    break
            got |= ok

        ok = True
        for i in range(3):
            if not check(self.table[i, i]):
                ok = False
                break
        got |= ok
        
        ok = True
        for i in range(3):
            if not check(self.table[i, 2-i]):
                ok = False
                break
        got |= ok

        return got
    
    def check_tie(self, players) -> bool:
        def check_full(self) -> bool:
            full = True
            for i in range(3):
                for j in range(3):
                    if self.table[i, j] == 0:
                        full = False
            self.full |= full
            return full
        
        if self.full or check_full(self):
            min0 = 10
            for i in range(3):
                for j in range(3):
                    if self.table[i, j] <= 9:
                        min0 = min(min0, self.table[i, j])
            min1 = 10
            for i in range(3):
                for j in range(3):
                    if self.table[i, j] > 9:
                        min1 = min(min1, self.table[i, j])

            return min0 >= max(players[1]) and min1 >= max(players[0])
        else:
            return False
    
    
class Game:
    def __init__(self) -> None:
        self.players = [set(list(i for i in range(1,10))),
                        set(list(i for i in range(1,10)))]
        self.table = Table()
        self.turn = 0
        self.end = False
    
    def show_table(self) -> None:
        pieces = list()
        for i in range(3):
            row_pieces = list()
            for j in range(3):
                row_pieces.append(self.table.get_piece(i, j))
            pieces.append(row_pieces)
        print(f"     1    2    3")
        print(f"   --------------")
        print(f"1 | {pieces[0][0]} | {pieces[0][1]} | {pieces[0][2]} |")
        print(f"   --------------")
        print(f"2 | {pieces[1][0]} | {pieces[1][1]} | {pieces[1][2]} |")
        print(f"   --------------")
        print(f"3 | {pieces[2][0]} | {pieces[2][1]} | {pieces[2][2]} |")
        print(f"   --------------")