from game import Game

game = Game()
while not game.end:
    print(f"O has: {', '.join(map(str, game.players[0]))}")
    print(f"X has: {', '.join(map(str, game.players[1]))}")
    print(f"{'O' if game.turn == 0 else 'X'} turn to move")
    game.show_table()
    print("Enter your move: ", end='')
    (r,c,n) = map(int,input().split())
    r -= 1
    c -= 1
    if n not in game.players[game.turn]:
        success = False
    else:
        success = game.table.put_piece(r, c, game.turn, n)
    while not success:
        print('Please re-enter your move: ', end='')
        (c,r,n) = map(int,input().split())
        r -= 1
        c -= 1
        if n not in game.players[game.turn]:
            continue
        success = game.table.put_piece(r, c, game.turn, n)
    game.players[game.turn].remove(n)
    print(game.table.get_piece(r, c))
    if game.table.check_win(0):
        print('O won!')
        game.show_table()
        game.end = True
    elif game.table.check_win(1):
        print('X won!')
        game.show_table()
        game.end = True
    elif game.table.check_tie(game.players):
        print('Tie')
        game.show_table()
        game.end = True
    game.turn = not game.turn