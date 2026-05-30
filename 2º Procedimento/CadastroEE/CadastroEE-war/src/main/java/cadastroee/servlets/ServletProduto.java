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
import java.io.PrintWriter;
import java.util.List;

@WebServlet(name = "ServletProduto", urlPatterns = {"/ServletProduto"})
public class ServletProduto extends HttpServlet {

    // Letra D: Injeção do componente EJB no Servlet
    @EJB
    private ProdutoFacadeLocal facade;

    protected void processRequest(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        // Define que a resposta será um HTML com acentuação correta
        response.setContentType("text/html;charset=UTF-8");
        
        // Busca a lista de produtos utilizando o nosso EJB Facade
        List<Produto> listaProdutos = facade.findAll();

        // Letra E: Modifica a resposta para apresentar os dados em formato de lista HTML
        try (PrintWriter out = response.getWriter()) {
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Lista de Produtos - CadastroEE</title>");            
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>Produtos Cadastrados</h1>");
            
            out.println("<ul>");
            if (listaProdutos == null || listaProdutos.isEmpty()) {
                out.println("<li>Nenhum produto encontrado no banco de dados.</li>");
            } else {
                for (Produto p : listaProdutos) {
                    out.println("<li><strong>ID:</strong> " + p.getIdProduto() + 
                                " | <strong>Nome:</strong> " + p.getNome() + 
                                " | <strong>Qtd:</strong> " + p.getQuantidade() + 
                                " | <strong>Preço:</strong> R$ " + p.getPrecoVenda() + "</li>");
                }
            }
            out.println("</ul>");
            
            out.println("</body>");
            out.println("</html>");
        }
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
}