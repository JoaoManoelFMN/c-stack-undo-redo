# Como Contribuir com o Projeto [Lista de tarefas usando pilha em C]


Para garantir que o processo seja tranquilo para todos, siga estas diretrizes.

## Tipos de Contribuição

Você pode contribuir de várias formas:

* **Reportando Bugs:** Encontrou algo que não funciona como deveria? Abra uma "Issue".
* **Sugerindo Melhorias:** Tem uma ideia para uma nova funcionalidade ou uma melhoria em algo que já existe? Abra uma "Issue" para discutirmos.
* **Escrevendo Código:** Quer corrigir um bug ou implementar uma funcionalidade? Siga o fluxo abaixo.
* **Melhorando a Documentação:** Viu um erro de digitação ou algo que poderia ser mais claro no `README.md` ou nos comentários do código? Faça um Pull Request!

## Reportando Bugs (Issues)

1.  Vá até a aba **"Issues"** do repositório.
2.  Clique em **"New Issue"**.
3.  Use um título claro e descritivo.
4.  Na descrição, por favor, inclua:
    * **O que você esperava que acontecesse?**
    * **O que de fato aconteceu?** (Inclua mensagens de erro, se houver).
    * **Passo a passo para reproduzir o bug.**
    * (Opcional) Qual sistema operacional e compilador você está usando.

## Sugerindo Melhorias (Issues)

1.  Vá até a aba **"Issues"**.
2.  Clique em **"New Issue"**.
3.  Descreva sua ideia em detalhes. Explique **qual problema** ela resolve ou **por que** ela seria útil para o projeto. Estamos abertos a discussões!

## Contribuindo com Código (Pull Requests)

Este é o fluxo de trabalho padrão para enviar seu código:

1.  **Faça um "Fork"** do repositório para a sua própria conta do GitHub.
2.  **Clone o seu fork** para a sua máquina local:
    ```bash
    git clone [https://github.com/JoaoManoelFMN/c-stack-undo-redo.git](https://github.com/SEU-USUARIO/NOME-DO-REPOSITORIO.git)
    ```
3.  **Crie uma nova "branch"** para suas alterações. Use um nome descritivo (ex: `feature/adiciona-funcao-peek` ou `bugfix/corrige-leak-no-pop`):
    ```bash
    git checkout -b feature/minha-nova-feature
    ```
4.  **Faça suas alterações** no código.
    * **Importante:** Adicione comentários ao seu código quando necessário.
    * **[Opcional, mas recomendado]** Se o projeto tiver testes, adicione testes para sua nova funcionalidade.
5.  **Adicione e "commite"** suas alterações com uma mensagem clara:
    ```bash
    git add .
    git commit -m "feat: Adiciona a funcionalidade X" 
    # ou "fix: Corrige o bug Y"
    ```
6.  **Envie sua branch** para o seu fork no GitHub:
    ```bash
    git push origin feature/minha-nova-feature
    ```
7.  **Abra um "Pull Request" (PR)** no repositório original.
    * Vá até o repositório original no GitHub.
    * Clique na aba **"Pull Requests"** e em **"New Pull Request"**.
    * Selecione a sua branch.
    * No título do PR, coloque um resumo do que foi feito.
    * Na descrição, **referencie a "Issue"** que este PR resolve (ex: `Resolve #12`) e explique o que você fez e por que.

## Processo de Revisão (Code Review)

Após você abrir um Pull Request, eu (como Tech Lead) ou outros mantenedores iremos revisá-lo.

* Podemos fazer perguntas ou sugerir alterações no seu PR. Isso é normal e faz parte do processo de colaboração para garantir a qualidade do código.
* Assim que seu PR for aprovado, ele será "mergeado" (incorporado) à branch principal do projeto.
* Seu nome aparecerá na lista de contribuidores!

Obrigado por ajudar a tornar este projeto melhor! 🎉