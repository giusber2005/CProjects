#include"../include/utils.h"

void graph_generator(SDL_Renderer** renderer, Graph graph);
void projector(SDL_Renderer** renderer, double (*func)(double));
void phasor(SDL_Renderer** renderer, Phasor phasor);
void window_manager(SDL_Renderer** renderer, Graph* graphList);

void free_everything(Graph* graphs, Phasor* phasors, Func* funcs) {
    Phasor* phasorsElt, phasorsTmp;
    Graph* graphsElt, graphsTmp;
    Func* funcsElt, funcsTmp;
    
    DL_FOREACH_SAFE(graphs, graphsElt, graphsTmp) {
      DL_DELETE(head,elt);
      free(elt);
    }
    
    DL_FOREACH_SAFE(graphs, graphsElt, graphsTmp) {
      DL_DELETE(head,elt);
      free(elt);
    }
    
    DL_FOREACH_SAFE(graphs, graphsElt, graphsTmp) {
      DL_DELETE(head,elt);
      free(elt);
    }
}