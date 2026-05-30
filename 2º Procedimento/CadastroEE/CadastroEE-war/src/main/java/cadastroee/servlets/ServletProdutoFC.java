package cadastroee.servlets;

import cadastroee.controller.ProdutoFacadeLocal;
import cadastroee.model.Produto;
import jakarta.ejb.EJB;
import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;
import java.io.IOException;



@WebServlet(name = "ServletProdutoFC", urlPatterns = {"/ServletProdutoFC"})
public class ServletProdutoFC extends HttpServlet {

    @EJB
    private ProdutoFacadeLocal facade; 

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String acao = request.getParameter("acao");
        if (acao == null) {
            acao = "listar"; 
        }

        String destino = "ProdutoLista.jsp";

        try {
            switch (acao) {
                
                case "listar":
                    request.setAttribute("produtos", facade.findAll());
                    break;

                case "formIncluir":
                    destino = "ProdutoDados.jsp";
                    break;

                case "formAlterar":
                    Integer idForm = Integer.parseInt(request.getParameter("id"));
                    // Se Produto ficar vermelho, use Ctrl+Shift+I
                    Produto produtoAlterar = facade.find(idForm); 
                    request.setAttribute("produto", produtoAlterar);
                    destino = "ProdutoDados.jsp";
                    break;

                case "excluir":
                    Integer idExcluir = Integer.parseInt(request.getParameter("id"));
                    Produto produtoExcluir = facade.find(idExcluir);
                    if (produtoExcluir != null) {
                        facade.remove(produtoExcluir);
                    }
                    request.setAttribute("produtos", facade.findAll());
                    break;

                case "alterar":
                    Integer idAlterar = Integer.parseInt(request.getParameter("id"));
                    Produto produtoEdit = facade.find(idAlterar);
                    
                    if (produtoEdit != null) {
                        produtoEdit.setNome(request.getParameter("nome"));
                        // Se o seu preço for Double, mude a linha abaixo para Double.parseDouble
                        produtoEdit.setPrecoVenda(Float.parseFloat(request.getParameter("preco"))); 
                        produtoEdit.setQuantidade(Integer.parseInt(request.getParameter("quantidade")));
                        facade.edit(produtoEdit);
                    }
                    request.setAttribute("produtos", facade.findAll());
                    break;

                case "incluir":
                    Produto novoProduto = new Produto();
                    novoProduto.setNome(request.getParameter("nome"));
                    // Se o seu preço for Double, mude a linha abaixo para Double.parseDouble
                    novoProduto.setPrecoVenda(Float.parseFloat(request.getParameter("preco")));
                    novoProduto.setQuantidade(Integer.parseInt(request.getParameter("quantidade")));
                    
                    facade.create(novoProduto);
                    request.setAttribute("produtos", facade.findAll());
                    break;
            }
        } catch (Exception e) {
            System.err.println("Erro ao processar a ação " + acao + ": " + e.getMessage());
        }

        request.getRequestDispatcher(destino).forward(request, response);
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        processRequest(request, response);
    }

    @Override
    public String getServletInfo() {
        return "Front Controller para gestão de Produtos";
    }
}