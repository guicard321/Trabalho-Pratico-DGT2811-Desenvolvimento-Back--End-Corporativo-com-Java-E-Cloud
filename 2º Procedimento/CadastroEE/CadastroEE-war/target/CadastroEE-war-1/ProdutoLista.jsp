<%@page import="java.util.List"%>
<%@page import="cadastroee.model.Produto"%>
<%@page contentType="text/html" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <title>Lista de Produtos</title>
        <style>
            body { font-family: Arial, sans-serif; margin: 20px; }
            table { border-collapse: collapse; width: 100%; margin-top: 20px; }
            th, td { border: 1px solid #ddd; padding: 8px; text-align: left; }
            th { background-color: #f2f2f2; }
            a { text-decoration: none; color: #0056b3; margin-right: 10px; }
            a:hover { text-decoration: underline; }
            .btn-novo { display: inline-block; padding: 10px 15px; background-color: #28a745; color: white; margin-bottom: 15px; }
        </style>
    </head>
    <body>
        <h1>Produtos Cadastrados</h1>
        
        <a href="ServletProdutoFC?acao=formIncluir" class="btn-novo">Incluir Novo Produto</a>
        
        <table>
            <tr>
                <th>ID</th>
                <th>Nome</th>
                <th>Quantidade</th>
                <th>Preço</th>
                <th>Ações</th>
            </tr>
            <%
                // Recupera a lista de produtos enviada pelo Servlet
                List<Produto> produtos = (List<Produto>) request.getAttribute("produtos");
                
                if (produtos != null && !produtos.isEmpty()) {
                    // Para cada elemento da lista...
                    for (Produto p : produtos) {
            %>
            <tr>
                <td><%= p.getIdProduto() %></td>
                <td><%= p.getNome() %></td>
                <td><%= p.getQuantidade() %></td>
                <td><%= p.getPrecoVenda() %></td>
                <td>
                    <a href="ServletProdutoFC?acao=formAlterar&id=<%= p.getIdProduto() %>">Alterar</a>
                    <a href="ServletProdutoFC?acao=excluir&id=<%= p.getIdProduto() %>" onclick="return confirm('Excluir este produto?');">Excluir</a>
                </td>
            </tr>
            <%
                    }
                } else {
            %>
            <tr>
                <td colspan="5">Nenhum produto cadastrado.</td>
            </tr>
            <%
                }
            %>
        </table>
    </body>
</html>