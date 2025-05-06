# Jogo da Forca em C

Este é um jogo em que o jogador precisa acertar a palavra proposta, tendo como dica o número de letras que a palavra tem e o tema ligado a palavra. O programa permite carregar ou iniciar novas partidas, salvar o progresso e voltar futuramente, registrar logs das jogadas e oferece dicas para ajudar o jogador a vencer.

# Funcionalidades

    1. Iniciar Partida: Escolha iniciar um novo jogo ou carregar um jogo já salvo.

    2. Exibição da Forca: Desenha a forca completa conforme os erros.

    3. Dica: Mostra uma palavra relacionada a palavra proposta.

    4. Tentativas: Até 8 tentativas de jogo.

    5. Salvar e Sair: Digite 1 durante o jogo para salvar o progresso e sair do jogo.

    6. Carregar Partida: Carrega o estado do jogo que foi salvo utilizando o salvar-forca.txt.

    7. Reiniciar Jogo: Permite jogar novamente quando uma partida é finalizada.

# Estrutura do Arquivo

O jogo utiliza arquivos .txt para salvar informações das partidas.

palavras-sortidas.txt: Lista de palavras e dicas.

salvar-forca.txt: armazena o progresso do jogo atual contendo dica, palavra a ser descoberta e letras corretas e erradas.

logs-forca.txt: armazena as ações do jogador dentro do programa contendo as horas, dica da palavra e a letra jogada.
