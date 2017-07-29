import {takeEvery} from 'redux-saga/effects';
import {LOGIN, CHECK_AUTH, LOGOUT} from '../actions/auth';

export function* authWatcher() {
	yield takeEvery(LOGIN, loginWorker);
	yield takeEvery(CHECK_AUTH, checkAuthWorker);
	yield takeEvery(LOGOUT, logoutWorker);
}

export function* loginWorker() {
	//todo
}

export function* checkAuthWorker() {
	//todo
}

export function* logoutWorker() {
	//todo
}
