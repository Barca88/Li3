/** @file interface.h
 *  @brief Protótipos das funções relacionadas com a interface.
 *
 *  O ficheiro contem os prototipos das funçoes que implementam o parser.
 *
 *  @author Grupo 19
 */

#include "date.h"
#include "pair.h"
#include "list.h"
#include "user.h"

/**
 * @brief Declaração do tipo TAD_community, um tipo abstrato. 
 */
typedef struct TCD_community * TAD_community;

/** @brief Inicialização da estrutura.
 *  @return TAD_community.
 */
TAD_community init();

/** @brief Carregamento dos ficheiros.
 *  @param TAD_community Estrutura.
 *  @param dump_path ficheiros.
 *  @return TAD_community.
 */
TAD_community load(TAD_community com, char* dump_path);  //Diretoria onde estarão os ficheiros do dump.

/* Protótipo das queries
*/
/** @brief retorna a informação dado o id de um post.
 *  @param TAD_community Estrutura.
 *  @param Id do post.
 *  @return Título e user criador do post.
 */
STR_pair info_from_post(TAD_community com, long id);  

/** @brief retorna os N utilizadores com maior numero de posts de sempre dado um int N. 
 *  @param TAD_community Estrutura.
 *  @param N nº de utilizadores pretendidos.
 *  @return Id dos N top utilizadores.
 */
LONG_list top_most_active(TAD_community com, int N);

/** @brief retorna o nº total de posts dadas duas datas arbitrárias. 
 *  @param TAD_community Estrutura.
 *  @param Date begin data inicial.
 *  @param Date end data final.
 *  @return nº total de posts (answer e quest) num intervalo de tempo arbitrário.
 */
LONG_pair total_posts(TAD_community com, Date begin, Date end);

/** @brief retorna todas as perguntas que contêm uma determinada tag dado duas datas. 
 *  @param TAD_community Estrutura.
 *  @param tag tag pretendida.
 *  @param Date begin data inicial.
 *  @param Date end data final.
 *  @return id das perguntas que contêm uma determinada tag.
 */
LONG_list questions_with_tag(TAD_community com, char* tag, Date begin, Date end);

/** @brief retorna a short bio e os ids dos últimos 10 posts dado o id de um utilizador. 
 *  @param TAD_community Estrutura.
 *  @param id do utilizador.
 *  @return informação do perfil de um utilizador e os ids dos seus últimos 10 posts.
 */
USER get_user_info(TAD_community com, long id);

/** @brief retorna ids das respostas com mais votos dado duas datas e um N nº respostas.
 *  @param TAD_community Estrutura.
 *  @param N nº de respostas pretendidas.
 *  @param Date begin data inicial.
 *  @param Date end data final.
 *  @return ids das N respostas com mais votos.
 */
LONG_list most_voted_answers(TAD_community com, int N, Date begin, Date end);

/** @brief retorna ids das perguntas com mais respostas dado duas datas e um N nº perguntas.
 *  @param TAD_community Estrutura.
 *  @param N nº de perguntas pretendidas.
 *  @param Date begin data inicial.
 *  @param Date end data final.
 *  @return ids das N perguntas com mais respostas.
 */
LONG_list most_answered_questions(TAD_community com, int N, Date begin, Date end);

/** @brief retorna ids das perguntas que contêm determinada palavra no título.
 *  @param TAD_community Estrutura.
 *  @param word palavra pretendida.
 *  @param N nº de perguntas pretendidas.
 *  @return lista com ids das N perguntas cujo título contem uma dada palavra.
 */
LONG_list contains_word(TAD_community com, char* word, int N);

/** @brief retorna nº de perguntas em que dois utilizadores participaram dado o id de cada utilizador e o N nº de perguntas.
 *  @param TAD_community Estrutura.
 *  @param id1 id do utilizador 1.
 *  @param id2 id do utilizador 2.
 *  @param N nº de perguntas. 
 *  @return últimas N perguntas em que participaram dois utilizadores.
 */
LONG_list both_participated(TAD_community com, long id1, long id2, int N);

/** @brief retorna a melhor resposta de uma pergunta dado o id da pergunta.
 *  @param TAD_community Estrutura.
 *  @param id id da pergunta. 
 *  @return obter a melhor resposta de uma determinada pergunta.
 */
long better_answer(TAD_community com, long id);

/** @brief retorna os ids das tags mais usadas pelos utilzadores dado um int N num determinado intervalo de tempo.
 *  @param TAD_community Estrutura.
 *  @param N nº de tags e utilizadores.
 *  @param Date begin data inicial.
 *  @param Date end data final.
 *  @return ids das N tags mais pelos N utilizadores com melhor reputação.
 */
LONG_list most_used_best_rep(TAD_community com, int N, Date begin, Date end);

/** @brief dá free na estrutura.
 *  @param TAD_community Estrutura
 */
TAD_community clean(TAD_community com);
