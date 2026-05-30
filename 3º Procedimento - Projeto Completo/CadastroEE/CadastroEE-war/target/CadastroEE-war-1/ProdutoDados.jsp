<%@page import="cadastroee.model.Produto"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Dados do Produto</title>
        <link href="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/css/bootstrap.min.css" rel="stylesheet">
        <script src="https://cdn.jsdelivr.net/npm/bootstrap@5.3.2/dist/js/bootstrap.bundle.min.js"></script>
    </head>
    
    <body class="container">
        <br>
        <h1>Cadastro de Produto</h1>

        <%
            Produto produto = (Produto) request.getAttribute("produto");
            String acao = (produto == null) ? "incluir" : "alterar";
            String id = (produto != null && produto.getIdProduto() != null) ? produto.getIdProduto().toString() : "";
            String nome = (produto != null && produto.getNome() != null) ? produto.getNome() : "";
            String quantidade = (produto != null && produto.getQuantidade() != null) ? produto.getQuantidade().toString() : "";
            String preco = (produto != null && produto.getPrecoVenda() != null) ? produto.getPrecoVenda().toString() : "";
            String textoBotao = (produto == null) ? "Incluir Produto" : "Salvar Alteração";
        %>

        <form action="ServletProdutoFC" method="POST" class="form">
            <input type="hidden" name="acao" value="<%= acao %>">
            <input type="hidden" name="id" value="<%= id %>">

            <div class="mb-3">
                <label class="form-label">Nome:</label>
                <input type="text" name="nome" class="form-control" value="<%= nome %>" required>
            </div>

            <div class="mb-3">
                <label class="form-label">Quantidade:</label>
                <input type="number" name="quantidade" class="form-control" value="<%= quantidade %>" required>
            </div>

            <div class="mb-3">
                <label class="form-label">Preço (R$):</label>
                <input type="number" step="0.01" name="preco" class="form-control" value="<%= preco %>" required>
            </div>

            <button type="submit" class="btn btn-primary"><%= textoBotao %></button>
            <br><br>
            <a href="ServletProdutoFC?acao=listar" class="btn btn-link">Voltar para a Lista</a>
        </form>
    </body>
</html>