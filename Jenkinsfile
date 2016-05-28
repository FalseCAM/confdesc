node {
  stage 'Checkout'
   checkout scm

  stage 'Build'
   sh 'mkdir -p build'
   sh 'cd build && cmake -DOPTION_BUILD_DOCS=1 .. && make && make pack'

  stage 'Package'
   sh 'cd build && make pack'

  stage 'PostBuild'
   publishHTML([allowMissing: false, alwaysLinkToLastBuild: false, keepAll: false, reportDir: 'build/docs/api-docs/html', reportFiles: 'index.html', reportName: 'Doxygen'])

}
