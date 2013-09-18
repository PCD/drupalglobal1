/**
 * @file
 * equalheights module javascript settings.
 */
(function($) {
  Drupal.behaviors.equalHeightsModule = {
    attach: function (context, settings) {
      var eqClass = Drupal.settings.equalHeightsModule;
      if (eqClass) {
        $(window).bind('resize', function () {
          equalHeightsTrigger();
        }).trigger('resize');
      }
      function equalHeightsTrigger() {
        $.each(eqClass, function(eqClass, setting) {
          var target = $(setting.selector);
          target.height('auto');
          target.imagesLoaded({
            callback: function($images, $proper, $broken) {
              this.equalHeights(setting.minheight, setting.maxheight).css('overflow', setting.overflow)
            }
          });
        });
      }

    }
  }
})(jQuery);
