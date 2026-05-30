<%@page import="cadastroee.model.Produto"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Dados do Produto</title>
        <style>
            body { font-family: Arial, sans-serif; margin: 20px; }
            .form-group { margin-bottom: 15px; }
            label { display: inline-block; width: 100px; font-weight: bold; }
            input[type="text"], input[type="number"] { width: 200px; padding: 5px; }
            button { padding: 8px 15px; background-color: #0056b3; color: white; border: none; cursor: pointer; }
        </style>
    </head>
    <body>
        <h1>Cadastro de Produto</h1>

        <%
            // Recupera a entidade enviada pelo Servlet
            Produto produto = (Produto) request.getAttribute("produto");
            
            // Define a variável acao e os dados (se existirem)
            String acao = (produto == null) ? "incluir" : "alterar";
            String id = (produto != null && produto.getIdProduto() != null) ? produto.getIdProduto().toString() : "";
            String nome = (produto != null && produto.getNome() != null) ? produto.getNome() : "";
            String quantidade = (produto != null && produto.getQuantidade() != null) ? produto.getQuantidade().toString() : "";
            String preco = (produto != null && produto.getPrecoVenda() != null) ? produto.getPrecoVenda().toString() : "";
            
            // Texto do botão adequado para as situações
            String textoBotao = (produto == null) ? "Incluir Produto" : "Salvar Alteração";
        %>

        <form action="ServletProdutoFC" method="POST">
            
            <input type="hidden" name="acao" value="<%= acao %>">
            
            <input type="hidden" name="id" value="<%= id %>">

            <div class="form-group">
                <label>Nome:</label>
                <input type="text" name="nome" value="<%= nome %>" required>
            </div>

            <div class="form-group">
                <label>Quantidade:</label>
                <input type="number" name="quantidade" value="<%= quantidade %>" required>
            </div>

            <div class="form-group">
                <label>Preço (R$):</label>
                <input type="number" step="0.01" name="preco" value="<%= preco %>" required>
            </div>

            <button type="submit"><%= textoBotao %></button>
            <br><br>
            <a href="ServletProdutoFC?acao=listar">Voltar</a>
        </form>
    </body>
</html>