import Abstract.Controller
import Abstract.Model
import IndexView

defclass IndexController isa Controller
  defcon init
    var infoList = {"CS364", "Software Engineering I", "Fall/Winter"}
    model_ = [Model initWithList:infoList]
    view_ = [IndexView initWithModel:model_]
  endcon
endclass
