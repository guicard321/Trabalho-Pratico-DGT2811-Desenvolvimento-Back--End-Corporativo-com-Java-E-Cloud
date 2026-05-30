package cadastroee.model;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import java.io.Serializable;

@Entity
public class Movimento implements Serializable {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer idMovimento;
    private Integer idUsuario;
    private Integer idPessoa;
    private Integer idProduto;
    private Integer quantidade;
    private String tipo;
    private Float valorUnitario;

    public Movimento() {
    }

    public Integer getIdMovimento() { return idMovimento; }
    public void setIdMovimento(Integer idMovimento) { this.idMovimento = idMovimento; }

    public Integer getIdUsuario() { return idUsuario; }
    public void setIdUsuario(Integer idUsuario) { this.idUsuario = idUsuario; }

    public Integer getIdPessoa() { return idPessoa; }
    public void setIdPessoa(Integer idPessoa) { this.idPessoa = idPessoa; }

    public Integer getIdProduto() { return idProduto; }
    public void setIdProduto(Integer idProduto) { this.idProduto = idProduto; }

    public Integer getQuantidade() { return quantidade; }
    public void setQuantidade(Integer quantidade) { this.quantidade = quantidade; }

    public String getTipo() { return tipo; }
    public void setTipo(String tipo) { this.tipo = tipo; }

    public Float getValorUnitario() { return valorUnitario; }
    public void setValorUnitario(Float valorUnitario) { this.valorUnitario = valorUnitario; }
}