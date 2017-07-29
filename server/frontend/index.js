import React from 'react';
import 'babel-polyfill';
import ReactDOM from 'react-dom';
import {createStore, combineReducers, applyMiddleware} from 'redux';
import {Provider} from 'react-redux';
import createHistory from 'history/createBrowserHistory';
import {Route} from 'react-router';
import {ConnectedRouter, routerReducer, routerMiddleware} from 'react-router-redux';
import createSagaMiddleware from 'redux-saga'

import reducers from './reducers';
import sagas from './sagas';
import Tasks from './pages/Tasks/Tasks';
import Auth from './pages/Auth/Auth.connected';

const history = createHistory();

const historyMiddleware = routerMiddleware(history);
const sagaMiddleware = createSagaMiddleware();

const store = createStore(
	combineReducers({
		...reducers,
		router: routerReducer
	}),
	applyMiddleware(historyMiddleware, sagaMiddleware)
);

sagaMiddleware.run(sagas);

ReactDOM.render(
	<Provider store={store}>
		<ConnectedRouter history={history}>
			<div>
				<Route path="/auth" component={Auth}/>
				<Route path="/" component={Tasks}/>
			</div>
		</ConnectedRouter>
	</Provider>,
	document.getElementById('root')
);